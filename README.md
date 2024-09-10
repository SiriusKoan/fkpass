# fkpass

A PAM module for fun.

Have you ever thought you typed the correct password but it was wrong?

If not, you can try this module to experience the feeling.

It only affects the SSH login.

## Installation

1. Clone this repository.

2. Run `make` to compile the module.

3. Run `sudo make install` to install the module.

### Configuration

You can change `prob` by updating `/etc/pam.d/sshd`.

This value is the probability of the module to deny the login.

```
auth   required    fkpass.so prob=0.1
```

## Uninstallation

1. Run `sudo make uninstall` to uninstall the module.
