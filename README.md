# tagd8-vagrant

A [Vagrant](https://www.vagrantup.com/) virtual machine configuration and provisioner,
for use as a test or development environment for Drupal applications.

**NOTE** this virtual machine should not be used in a production environment.

## Usage
The Vagrant configuration and [Puppet](https://puppetlabs.com/) provisioning scripts
are contained in the `/private` directory. Using the VM can be accomplished via
the following steps:

* Install [Vagrant](https://www.vagrantup.com/).
* Copy the entire `/private` directory to the root directory of your Drupal codebase.
* Copy the `/private/example.config.yml` to `/private/config.yml`, and edit it with your preferred hostname and IP address.
* From the `/private` directory, run `vagrant up`. This will create and provision the VM.
* Run `vagrant plugin install vagrant-hostsupdater` to install a plugin to handle adding your host to `/etc/hosts`.
* Create or load your site database into the VM `mysql` server. For testing purposes the provisioner creates a user and database named `vagrant`.
* Connect to your new test site in your browser at the URL you've chosen.
* Your site code is mounted on the Vagrant VM in the `/vagrant` directory.

## Bonuses

In the `/private` directory there is a folder for things to add to your docroot.

* `tag_dev` -  A module that supplies customizable `drush golocal`, `drush godev`, and `drush gotest` commands. Feel free to add onto them for project specific reasons to make your development experience smoother.
