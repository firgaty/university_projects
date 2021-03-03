NAME ?= flex

LEX = flex
YACC = bison -y
YFLAGS  = -d

scan: scan.l
	scan.l vars_scan.l

# clean:
# 	rm -f scan *.c *.a *.gch