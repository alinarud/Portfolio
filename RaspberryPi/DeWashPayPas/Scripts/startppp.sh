iptables -A FORWARD -i ppp0 -j ACCEPT
iptables -A FORWARD -o ppp0 -j ACCEPT
iptables -t nat -A POSTROUTING -o wlan0 -j MASQUERADE

#rm /run/lock/LCK..ttyACM0

while true; do
   if [ -r /dev/ttyACM0 ]; then
      pppd file /home/pi/DeWashPayPas/Scripts/ppp-usb
   fi
done

