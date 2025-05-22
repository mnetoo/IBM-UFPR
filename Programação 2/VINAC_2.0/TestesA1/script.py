import subprocess

EXEC_LINE = "./vina"
SHOW_TEST = "cat"
PATHF = './files'
FILES = ['chatgpt-5k.txt', 'chatgpt-40k.txt', 'img.jpeg', 'radio-100k.bin', 'radio.cfg']
CMD_TEST = {}

# T1 - Teste de inserção plana e extração
CMD_TEST[1] = [
	f'cp {PATHF}/{FILES[0]} .',                # cp files/chatgpt-5k.txt .
	
	f'{EXEC_LINE} -p arc1.vc {FILES[0]}',     # vina -p arc1.vc chatgpt-5k.txt

	f'rm {FILES[0]}',                          # rm chatgpt-5k.txt

	f'{EXEC_LINE} -x arc1.vc {FILES[0]}',      # vina -x arc1.vc chatgpt-5k.txt

	f'diff {PATHF}/{FILES[0]} {FILES[0]}',     # diff files/chatgpt-5k.txt chatgpt-5k.txt

	f'rm arc1.vc',                             # rm arc1.vc

	f'rm {FILES[0]}',                          # rm chatgpt-5k.txt
]

# T2 - Teste de inserção comprimida e extração 
CMD_TEST[2] = [
	f'cp {PATHF}/{FILES[1]} .',                # cp files/chatgpt-40k.txt .

	f'{EXEC_LINE} -p arc1.vc {FILES[1]}',     # vina -i arc1.vc chatgpt-40k.txt

	f'rm {FILES[1]}',                          # rm chatgpt-5k.txt

	f'{EXEC_LINE} -x arc1.vc {FILES[1]}',      # vina -x arc1.vc chatgpt-40k.txt

	f'diff {PATHF}/{FILES[1]} {FILES[1]}',     # diff files/chatgpt-40k.txt chatgpt-40k.txt

	f'rm arc1.vc',                             # rm arc1.vc

	f'rm {FILES[1]}',                          # rm chatgpt-40k.txt
]

# T3 - Teste de extração (all)
CMD_TEST[3] = [
	f'cp {PATHF}/{FILES[0]} {PATHF}/{FILES[1]} {PATHF}/{FILES[2]} .',  # cp files/chatgpt-5k.txt files/chatgpt-40k.txt files/img.jpeg .
                                               
	f'{EXEC_LINE} -p arc1.vc {FILES[0]} {FILES[1]} {FILES[2]}',	   # vina -p arc1.vc chatgpt-5k.txt chatgpt-40k.txt img.jpeg
	                                           
	f'rm {FILES[0]} {FILES[1]} {FILES[2]}',          				   # rm chatgpt-5k.txt chatgpt-40k.txt img.jpeg                
                                               
	f'{EXEC_LINE} -x arc1.vc',                 						   # vina -x arc1.vc chatgpt-40k.txt
	
	f'diff {PATHF}/{FILES[0]} {FILES[0]}',     						   # diff files/chatgpt-5k.txt chatgpt-40k.txt
	
	f'diff {PATHF}/{FILES[1]} {FILES[1]}',     						   # diff files/chatgpt-40k.txt chatgpt-40k.txt
	
	f'diff {PATHF}/{FILES[2]} {FILES[2]}',     						   # diff files/img.jpeg img.jpeg
	
	f'rm arc1.vc',                             						   # rm arc1.vc
	
	f'rm {FILES[0]} {FILES[1]} {FILES[2]}',    						   # rm chatgpt-5k.txt chatgpt-40k.txt img.jpeg                                                              
]

# T4 - Teste de reinserção plana no começo (menor-reorganização) e extração
CMD_TEST[4] = [
	f'cp {PATHF}/{FILES[1]} {PATHF}/{FILES[2]} {PATHF}/{FILES[3]} .', # cp files/chatgpt-40k.txt files/img.jpeg files/radio-100k.bin .
                                               
	f'{EXEC_LINE} -p arc1.vc {FILES[1]} {FILES[2]} {FILES[3]}',	  # login/vina -p arc1.vc chatgpt-40k.txt img.jpeg radio-100k.bin
	                                           
	f'rm {FILES[1]} {FILES[2]} {FILES[3]}',							  # rm chatgpt-40k.txt img.jpeg radio-100k.bin
                                               
	f'cp {PATHF}/{FILES[0]} {FILES[1]}',							  # cp files/chatgpt-5k.txt chatgpt-40k
                                               
	f'{EXEC_LINE} -p arc1.vc {FILES[1]}',							  # vina -p arc1.vc chatgpt-40k.txt
	                                           
	f'rm {FILES[1]}',												  # rm chatgpt-40k
	
	f'{EXEC_LINE} -x arc1.vc {FILES[1]} {FILES[2]}',				  # vina -x arc1.vc chatgpt-40k.txt img.jpeg
	
	f'diff {PATHF}/{FILES[0]} {FILES[1]}',     						  # diff files/chatgpt-40k.txt chatgpt-5k.txt
	
	f'diff {PATHF}/{FILES[2]} {FILES[2]}',     						  # diff files/img.jpeg img.jpeg
	
	f'rm arc1.vc',                             						  # rm arc1.vc
	
	f'rm {FILES[1]} {FILES[2]}',									  # rm chatgpt-40k.txt img.jpeg
]

# T5 - Teste de reinserção comprimida no meio (maior-reorganização) e extração
CMD_TEST[5] = [
	f'cp {PATHF}/{FILES[0]} {PATHF}/{FILES[2]} {PATHF}/{FILES[3]} .',  # cp files/chatgpt-5k.txt files/img.jpeg files/radio-100k.bin .
                                               
	f'{EXEC_LINE} -p arc1.vc {FILES[2]} {FILES[0]} {FILES[3]}',	   # vina -p arc1.vc img.jpeg chatgpt-5k.txt radio-100k.bin
	                                           
	f'rm {FILES[0]} {FILES[2]} {FILES[3]}',							   # rm chatgpt-5k.txt img.jpeg radio-100k.bin
                                               
	f'cp {PATHF}/{FILES[1]} {FILES[0]}',							   # cp files/chatgpt-40k.txt chatgpt-5k.txt
                                               
	f'{EXEC_LINE} -i arc1.vc {FILES[0]}',							   # vina -i arc1.vc chatgpt-5k.txt
	                                           
	f'rm {FILES[0]}',						   						   # rm chatgpt-5k.txt

	f'{EXEC_LINE} -x arc1.vc {FILES[0]}',	  						   # login/vina -x arc1.vc chatgpt-5k.txt
	                                           
	f'{EXEC_LINE} -x arc1.vc {FILES[3]}',							   # login/vina -x arc1.vc radio-100k.bin
	                                           
	f'diff {PATHF}/{FILES[1]} {FILES[0]}',     						   # diff files/chatgpt-40k.txt chatgpt-5k.txt
	
	f'diff {PATHF}/{FILES[3]} {FILES[3]}',     						   # diff files/radio-100k.bin radio-100k.bin
	
	f'rm arc1.vc',                             						   # rm arc1.vc
	
	f'rm {FILES[0]} {FILES[3]}',									   # rm chatgpt-5k.txt radio-100k.bin
]

# T6 - Teste de remoção com inserção plana e comprida
CMD_TEST[6] = [
	f'cp {PATHF}/{FILES[0]} {PATHF}/{FILES[1]} {PATHF}/{FILES[2]} {PATHF}/{FILES[3]} .',  # cp files/chatgpt-5k.txt files/chatgpt-40k.txt files/img.jpeg files/radio-100k.bin .
                                               
	f'{EXEC_LINE} -p arc1.vc {FILES[1]} {FILES[2]}',    								  # vina -p arc1.vc chatgpt-40k img.jpeg
	                                           
	f'{EXEC_LINE} -i arc1.vc {FILES[3]} {FILES[0]}',    								  # vina -i arc1.vc radio-100k.bin chatgpt-5k.txt
	                                           
	f'rm {FILES[0]} {FILES[1]} {FILES[2]} {FILES[3]}',               					  # rm chatgpt-5k.txt chatgpt-40k.txt img.jpeg radio-100k.bin           
                                               
	f'{EXEC_LINE} -r arc1.vc {FILES[1]}',      											  # vina -r arc1.vc chatgpt-40k.txt

	f'{EXEC_LINE} -x arc1.vc {FILES[3]}',      											  # vina -x arc1.vc radio-100k.bin
	
	f'diff {PATHF}/{FILES[3]} {FILES[3]}',     											  # diff files/radio-100k.bin radio-100k.bin
	
	f'rm arc1.vc',                             											  # rm arc1.vc
	
	f'rm {FILES[3]}',                          											  # rm radio-100k.bin
]

# T7 - Teste de movimentação - ABCDE - move D para o início do arquivo => DABCE
CMD_TEST[7] = [
	f'cp {PATHF}/{FILES[0]} {PATHF}/{FILES[1]} {PATHF}/{FILES[2]} {PATHF}/{FILES[3]} {PATHF}/{FILES[4]} .',	  						# cp files/chatgpt-5k.txt files/chatgpt-40k.txt files/img.jpeg files/radio-100k.bin files/radio.cfg .
                                               
	f'{EXEC_LINE} -i arc1.vc {FILES[0]} {FILES[4]}',  														  						# vina -i arc1.vc chatgpt-5k.txt radio.cfg  
	                                           
	f'{EXEC_LINE} -p arc1.vc {FILES[1]} {FILES[2]} {FILES[3]}',											  						# vina -p arc1.vc chatgpt-40k.txt img.jpeg radio-100k.bin    
	                                           
	f'rm {FILES[0]} {FILES[1]} {FILES[2]} {FILES[3]} {FILES[4]}',   										  						# rm chatgpt-5k.txt chatgpt-40k.txt img.jpeg radio-100k.bin radio.cfg                       
                                               
	[f'{EXEC_LINE} -m {FILES[2]} arc1.vc NULL', f'{EXEC_LINE} -m {FILES[2]} arc1.vc null', f'{EXEC_LINE} -m {FILES[2]} arc1.vc',
	f'{EXEC_LINE} -m arc1.vc {FILES[2]} NULL', f'{EXEC_LINE} -m arc1.vc {FILES[2]} null', f'{EXEC_LINE} -m arc1.vc {FILES[2]}'],    # vina -m img.jpeg arc1.vc NULL
                                               
	f'{EXEC_LINE} -x arc1.vc {FILES[2]} {FILES[3]}',      													  						# vina -m img.jpeg arc1.vc  radio-100k.bin
                                               
	f'diff {PATHF}/{FILES[2]} {FILES[2]}',     																  						# diff files/img.jpeg img.jpeg
	
	f'diff {PATHF}/{FILES[3]} {FILES[3]}',     																  						# diff files/chatgpt-40k.txt chatgpt-40k.txt
	
	f'rm arc1.vc',                             																  						# rm arc1.vc
	
	f'rm {FILES[2]} {FILES[3]}',               																  						# rm img.jpeg chatgpt-40k.txt
]

# T8 - Teste de movimentação - ABCDE - move B pra depois de D => ACDBE
CMD_TEST[8] = [
	f'cp {PATHF}/{FILES[0]} {PATHF}/{FILES[1]} {PATHF}/{FILES[2]} {PATHF}/{FILES[3]} {PATHF}/{FILES[4]} .',  # cp files/chatgpt-5k.txt files/chatgpt-40k.txt files/img.jpeg files/radio-100k.bin files/radio.cfg .
                                               
	f'{EXEC_LINE} -i arc1.vc {FILES[2]} {FILES[1]} {FILES[3]}',    										 # vina -i arc1.vc chatgpt-40k.txt img.jpeg radio-100k.bin
	                                           
	f'{EXEC_LINE} -p arc1.vc {FILES[0]} {FILES[4]}',    													 # vina -i arc1.vc chatgpt-5k.txt radio.cfg
	                                           
	f'rm {FILES[0]} {FILES[1]} {FILES[2]} {FILES[3]} {FILES[4]}',         									 # rm chatgpt-5k.txt chatgpt-40k.txt img.jpeg radio-100k.bin radio.cfg                 
                                               
	[f'{EXEC_LINE} -m {FILES[1]} arc1.vc {FILES[0]}', f'{EXEC_LINE} -m arc1.vc {FILES[1]} {FILES[0]}'],      # vina -m chatgpt-40k.txt arc1.vc chatgpt-5k.txt
                                               
	f'{EXEC_LINE} -x arc1.vc {FILES[1]} {FILES[0]}',      													 # vina -m chatgpt-40k.txt arc1.vc chatgpt-5k.txt
                                               
	f'diff {PATHF}/{FILES[0]} {FILES[0]}',     																 # diff files/chatgpt-5k.txt chatgpt-5k.txt
	
	f'diff {PATHF}/{FILES[1]} {FILES[1]}',     																 # diff files/chatgpt-40k.txt chatgpt-40k.txt
	
	f'rm arc1.vc',                             																 # rm arc1.vc
	
	f'rm {FILES[0]} {FILES[1]}',               																 # rm chatgpt-5k.txt chatgpt-40k.txt
]

# T9 - Teste de movimentação - ABCDE - move B pra depois de D => ACDBE => move A para depois de B => CDBAE
CMD_TEST[9] = [
	f'cp {PATHF}/{FILES[0]} {PATHF}/{FILES[1]} {PATHF}/{FILES[2]} {PATHF}/{FILES[3]} {PATHF}/{FILES[4]} .',  # cp files/chatgpt-5k.txt files/chatgpt-40k.txt files/img.jpeg files/radio-100k.bin files/radio.cfg .
                                               
	f'{EXEC_LINE} -i arc1.vc {FILES[2]} {FILES[1]} {FILES[3]}',    										 # vina -i arc1.vc img.jpeg chatgpt-40k.txt radio-100k.bin
	                                           
	f'{EXEC_LINE} -p arc1.vc {FILES[0]} {FILES[4]}',    													 # vina -i arc1.vc chatgpt-5k.txt radio.cfg
	                                           
	f'rm {FILES[0]} {FILES[1]} {FILES[2]} {FILES[3]} {FILES[4]}',         									 # rm chatgpt-5k.txt chatgpt-40k.txt img.jpeg radio-100k.bin radio.cfg                 
    
    f'cp arc1.vc arc1_cp.vc',										                                         # cp arc1.vc arc1_cp.vc  
	
	[f'{EXEC_LINE} -m {FILES[1]} arc1.vc {FILES[0]}', f'{EXEC_LINE} -m arc1.vc {FILES[1]} {FILES[0]}'],      # vina -m chatgpt-40k.txt arc1.vc chatgpt-5k.txt
                                               
	[f'{EXEC_LINE} -m {FILES[2]} arc1.vc {FILES[1]}', f'{EXEC_LINE} -m arc1.vc {FILES[2]} {FILES[1]}'],		 # vina -m img.jpeg chatgpt-40k.txt

	f'{EXEC_LINE} -x arc1.vc {FILES[1]} {FILES[2]}',      													 # vina -x chatgpt-40k.txt arc1.vc img.jpeg
                                               
	f'diff {PATHF}/{FILES[1]} {FILES[1]}',     																 # diff files/chatgpt-40k.txt chatgpt-40k.txt
	
	f'diff {PATHF}/{FILES[2]} {FILES[2]}',     																 # diff files/img.jpeg.txt img.jpeg.txt
	
	f'cmp -l arc1.vc arc1_cp.vc',																	 		 # cmp -l arc1.vc arc1_cp.vc

	f'wc -l cmp_file.txt',																 		 			 # wc -l cmp_file.txt

	f'rm arc1.vc arc1_cp.vc cmp_file.txt',                             										 # rm arc1.vc arc1_cp.vc cmp_file.txt
	
	f'rm {FILES[1]} {FILES[2]}',               																 # rm chatgpt-40k.txt img.jpeg
]


REPLACE_FLAGS = False
STEP_EXECUTION = False

for test in [1,2,3,4,5,6,7,8,9]:
	print("========================== EXECUTING TEST #" + str(test) + " ==========================")
	for command in CMD_TEST[test]:
		if type(command) == str:
			if REPLACE_FLAGS and "-p" in command:
				command = command.replace("-p", "-p")
			if REPLACE_FLAGS and "-i" in command:
				command = command.replace("-i", "-i")
			print("EXECUTING:", command)
			if command.startswith("diff"):
				diff_file = open("diff_file.txt", "wb+")
				try:
					result = subprocess.run(command.split(), timeout=10, stdout = diff_file)
				except:
					continue
				if (result.returncode != 0):
					input("ERRO - Verifique o diff_file.txt e pressione ENTER para continuar...")
				else:
					print("SUCESSO -", result)
				try:
					result = subprocess.run(["rm", "diff_file.txt"], timeout=10, stdout = diff_file)
				except:
					continue
			elif command.startswith("cmp"):
				cmp_file = open("cmp_file.txt", "wb+")
				try:
					result = subprocess.run(command.split(), timeout=10, stdout = cmp_file)
				except:
					continue
				cmp_file.close()
			elif command.startswith("wc"):
				try:
					result = subprocess.run(command.split(), timeout=10)
				except:
					continue
			else:
				try:
					result = subprocess.run(command.split(), timeout=10, stdout = subprocess.DEVNULL)
				except:
					continue
				if (result.returncode != 0):
					print("ERRO -", result)
				else:
					print("SUCESSO -", result)
		else:
			print("---")
			for subcommand in command:
				try:
					result = subprocess.run(subcommand.split(), timeout=10, stdout = subprocess.DEVNULL)
				except:
					continue
				if (result.returncode != 0):
					print("ERRO -", result)
				else:
					print("SUCESSO -", result)
					break
			print("---")

		if (STEP_EXECUTION):
			input("Pressione ENTER para continuar...")
	print("=======================================================================\n")
