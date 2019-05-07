SOUR:=$(wildcard *.cc)
ELF:=VMtranslator
OBJS:=$(SOUR:%.cc=%.o)
$(ELF):$(SOUR)
	g++ $^ -o $@
clean:
	rm -rf $(ELF) $(OBJS)
