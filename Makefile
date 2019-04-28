SOUR:=$(wildcard *.cc)
ELF:=assembler
OBJS:=$(SOUR:%.cc=%.o)
$(ELF):$(SOUR)
	g++ $^ -o $@
clean:
	rm -rf $(ELF) $(OBJS)
