all: build

build:
	gcc -fPIC -fno-stack-protector -c src/pam.c -o pam_fkpass.o
	ld -x --shared -o pam_fkpass.so pam_fkpass.o

install:
	cp pam_fkpass.so /lib/x86_64-linux-gnu/security/pam_fkpass.so

clean:
	rm pam_fkpass.o pam_fkpass.so
