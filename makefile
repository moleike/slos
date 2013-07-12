
all :
	@echo --
	@echo -- Application 1 .................................
	@echo --
	cd build/obj/apps/task1 ; make all
	@echo -- 
	@echo -- Application 2 .................................
	@echo --
	cd build/obj/apps/task2 ; make all
	@echo --
	@echo -- Application 3 .................................
	@echo --
	cd build/obj/apps/task3 ; make all
	@echo --
	@echo -- Kernel ........................................
	@echo --
	cd build/obj ; make all
	@echo --
	@echo -- Complete ........................................
	@echo --