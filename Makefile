all: build

build:
	gcc -fPIC -fno-stack-protector -c src/pam.c -o pam_fkpass.o
	ld -x --shared -o pam_fkpass.so pam_fkpass.o

install:
	cp pam_fkpass.so /lib/x86_64-linux-gnu/security/pam_fkpass.so
	cp /etc/pam.d/sshd /etc/pam.d/sshd.bak
	sed -i '/\@include common-auth/a auth required pam_fkpass.so' /etc/pam.d/sshd

uninstall:
	rm /lib/x86_64-linux-gnu/security/pam_fkpass.so
	sed -i '/auth required pam_fkpass.so/d' /etc/pam.d/sshd

clean:
	rm pam_fkpass.o pam_fkpass.so
