#!/usr/bin/env bash
	
read time < time.in

while true; do
  rm -f weather.html
  wget http://www.gismeteo.by/weather-minsk-4248/ -O weather.html 2> /dev/null
  grep -m 1 -oP "(?<=<dd class='value m_temp c'>).*?(?=<span class=\"meas\">)" weather.html
  sleep $time
done

