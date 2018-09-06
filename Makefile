# Makefile for serial calendar.
# D. L. Yonge-Mallo

GPP = g++

default : generate_cal mydate

print_tests : generate_tests
	./generate_tests | lpr -Pljp_plg -h

print_cal : generate_cal
	./generate_cal > calendar.tex
	latex calendar
	dvips calendar
	ps2pdf calendar.ps
	evince calendar.pdf &

edit :
	gvim generate_cal.cpp

mydate : mydate.cpp date.o gregor.o dow.o
	$(GPP) mydate.cpp date.o gregor.o dow.o -o mydate

generate_cal : generate_cal.cpp date.o gregor.o dow.o
	$(GPP) generate_cal.cpp date.o gregor.o dow.o -o generate_cal

sercal : sercal.cpp date.o gregor.o dow.o
	$(GPP) sercal.cpp date.o gregor.o dow.o -o sercal

generate_tests : generate_tests.cpp date.o gregor.o dow.o
	$(GPP) generate_tests.cpp date.o gregor.o dow.o -o generate_tests

date.o : date.cpp date.h
	$(GPP) date.cpp -c

gregor.o : gregor.c sdncal.h
	$(GPP) gregor.c -c

dow.o : dow.c sdncal.h
	$(GPP) dow.c -c
