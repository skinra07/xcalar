import paramiko
import sys
import getopt
import time

host_file = ''
private_key_file = ''
user = 'developer'
ssh_config_file = '/etc/ssh/sshd_config_test'

commands_rhel7 = [
    'sudo yum install openssh-server',
    "sudo sed -i 's/PasswordAuthentication yes/PasswordAuthentication no/' /etc/ssh/sshd_config"
    'sudo systemctl restart sshd']

commands_rhel6 = [
    'sudo yum install openssh-server',
    "sudo sed -i 's/PasswordAuthentication yes/PasswordAuthentication no/' /etc/ssh/sshd_config"
    'sudo service sshd restart',
    'chkconfig sshd on']

commands_ubuntu = [
    'sudo apt-get install openssh-server',
    "sudo sed -i 's/PasswordAuthentication yes/PasswordAuthentication no/' /etc/ssh/sshd_config"
    'sudo service ssh restart']


# This is main function that will execute list of commands based on OS type.
def do_work(host):
    ok = True
    try:
        status, ssh_client = create_connection(host)
        ok = status
        if status:
            cmds_list = os_info(ssh_client)
            if cmds_list is None:
                ok = False
            else:
                for cmd in cmds_list:
                    output, error = execute_command(ssh_client, cmd)

                    # parse result content of success/failure
                    for result in output:
                        print(result)
                    if error:
                        ok = False
                        print(error)
                        break;
    except Exception as e:
        print(e)
    finally:
        if ssh_client is not None:
            ssh_client.close()

    return ok


# determine distro type
def os_info(ssh_client):
    cmds = []
    command = 'cat /etc/os-release'
    output, error = execute_command(ssh_client, command)

    for result in output:
        if result.find('Ubuntu 14') != -1:
            cmds = commands_ubuntu
            break;
        if result.find('Red Hat Enterprise Linux Server 7') != -1:
            cmds = commands_rhel7
            break;
        if result.find('Red Hat Enterprise Linux Server 6') != -1:
            cmds = commands_rhel6
            break;
        if result.find('CentOS Linux 7') != -1:
            cmds = commands_rhel7
            break;

    if error:
        print(result)

    return cmds


# Get ssh connection
def create_connection(host):
    connect = True
    i = 1

    while True:
        print("Trying to connect to %s (%i/30)" % (host, i))

        try:
            ssh = paramiko.SSHClient()
            ssh.set_missing_host_key_policy(paramiko.AutoAddPolicy())
            ssh.connect(hostname=host, username=user, key_filename=private_key_file)
            print("Connected to %s" % host)
            break
        except paramiko.AuthenticationException:
            print("Authentication failed when connecting to %s" % host)
            connect = False
            return connect, ssh
        except paramiko.SSHException:
            print("Could not SSH to %s, waiting for it to start" % host)
            i += 1
            time.sleep(2)

        # If we could not connect within time limit
        if i == 30:
            print("Could not connect to %s. Giving up" % host)
            connect = False

    return connect, ssh


# this function basically execute commands provided and get the result
def execute_command(ssh_client, command):
    # Send the command (non-blocking)
    _, stdout, stderr = ssh_client.exec_command(command)

    # Wait for the command to terminate
    while not stdout.channel.exit_status_ready() and not stdout.channel.recv_ready():
        time.sleep(1)

    std_out = stdout.readlines()
    std_err = stderr.readlines()

    return std_out, std_err


# This function read host and private key filename
def read_arguments():
    global host_file
    global private_key_file
    try:
        myopts, args = getopt.getopt(sys.argv[1:], "h:k:")
    except getopt.GetoptError as e:
        print(str(e))
        print("Usage: %s -h host_file -k private_key_file" % sys.argv[0])
        sys.exit(2)

    for o, a in myopts:
        if o == '-h':
            host_file = a
        elif o == '-k':
            private_key_file = a

    print('host file={0}, private_key_file={1}'.format(host_file, private_key_file))


# read host file and store into memory list
def read_host_file():
    line_list = list()
    try:
        # open file in write mode
        with open(host_file, 'r') as f:
            for line in f:
                line_list.append(line.strip())

            f.close()
    except Exception as e:
        print(e)
        line_list = []

    return line_list


# Main function
def main():
    read_arguments()
    host_list = read_host_file()

    if host_list is None:
        print("No host in host file")
        sys.exit(1)

    for host in host_list:
        do_work(host)


if __name__ == '__main__':
    main()
    sys.exit(0)



