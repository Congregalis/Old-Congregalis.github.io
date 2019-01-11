# Makefile for schedule

all: schedule

schedule: schedule.cpp
	g++ schedule.cpp -o schedule

install: schedule
	install -m 755 schedule /usr/local/bin/schedule

uninstall: /usr/local/bin/schedule
	rm -f /usr/local/bin/schedule

clean:
	rm -f schedule
