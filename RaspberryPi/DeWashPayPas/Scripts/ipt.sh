iptables -A FORWARD -i ppp0 -j ACCEPT
iptables -A FORWARD -o ppp0 -j ACCEPT
iptables -t nat -A POSTROUTING -o eth0 -j MASQUERADE
