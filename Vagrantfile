# -*- mode: ruby -*-
# vi: set ft=ruby :

# This Vagrantfile defines the requirements of a Linux development environment
# to develop/run Git. This environment can be set up conveniently by installing
# Vagrant and VirtualBox and calling "vagrant up" in the Git directory.
#
# See https://github.com/msysgit/msysgit/wiki/Vagrant for details.

# Vagrantfile API/syntax version. Don't touch unless you know what you're doing!
VAGRANTFILE_API_VERSION = "2"

$provision = <<PROVISION
apt-get update
apt-get install -y make gcc libexpat-dev libcurl4-openssl-dev gettext tk8.5 libsvn-perl

# clean .profile in case we're re-provisioning
n="$(grep -n 'cd /vagrant' < /home/vagrant/.profile 2> /dev/null |
	sed 's/:.*//')"
test -z "$n" || {
	head -n $(($n-1)) < /home/vagrant/.profile > /tmp/.profile
	mv /tmp/.profile /home/vagrant/.profile
}

# add a nice greeting
cat >> /home/vagrant/.profile << \EOF

cd /vagrant/git
export PATH=/home/vagrant/bin:$PATH
cat << \TOOEOF

Welcome to the Vagrant setup for Git!
--------------------------------------

To build & install Git, just execute

	make -j NO_PERL_MAKEMAKER=t install

For more information, see https://github.com/msysgit/msysgit/wiki/Vagrant and
remember that this project is only as good as you make it.
TOOEOF
EOF

cat << EOF

Now that everything is set up, connect to the Vagrant machine with the command:

	vagrant ssh

EOF
PROVISION

Vagrant.configure(VAGRANTFILE_API_VERSION) do |config|
  # Start with a 64-bit Ubuntu 12.04 "Precise Penguin" box
  config.vm.box = "ubuntu"
  config.vm.box_url = "http://files.vagrantup.com/precise64.box"

  config.vm.provision :shell, :inline => $provision
end
