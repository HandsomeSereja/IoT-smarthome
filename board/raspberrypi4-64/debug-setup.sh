#!/bin/sh
#Скрипт для DEBUG сборки

TARGET_DIR="$1"

echo "DEBUG: Setting up network and SSH for development"

#1. Подключение к сети и получение ip адреса
cat > "${TARGET_DIR}/etc/init.d/S40network" << 'EOF'
#!/bin/sh
case "$1" in
	start)
		echo "Starting network..."
		ip link set eth0 up
		udhcpc -i eth0 -b -q
		;;
	stop)
		killall udhcpc
		ip link set eth0 down
		;;
esac
exit 0
EOF
chmod +x "${TARGET_DIR}/etc/init.d/S40network"

#2. Настройка SSH для входа под root с помощью пароля
if [ -f "${TARGET_DIR}/etc/ssh/sshd_config" ]; then
	sed -i 's/^#*PermitRootLogin.*/PermitRootLogin yes/' "${TARGET_DIR}/etc/ssh/sshd_config"
	sed -i 's/^#*PasswordAuthentication.*/PasswordAuthentication yes/' "${TARGET_DIR}/etc/ssh/sshd_config"
	echo "DEBUG: SSH configured for root password login"
fi	
