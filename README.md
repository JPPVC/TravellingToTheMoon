
TRANSCREVER Versão final para o documento word no modelo SNEA


NOTA COMO é um simulador o assembler não precisa estar de acordo com 
a endianess do ACG original porém seria bom implementar os aspectos estranhos
de como o ACG faz a leitura de binarios. O qual é complicado e involve um zero negativo 

#RESUMO 1* versão: 167 PALAVRAS
	Jogos são uma proposta famosa para integrar ensino e diversão no mesmo
	ambiente, especialmente para crianças mais novas. Visando isso com 
	proposito de ensinar o público sobre a historia e conceitos da 
	astronomia. Sera criado um simulador interativo e com camadas de 
	abstração sobre o funcionamento, história e conceitos envolvidos
	no lancamento da Apollo 11 e seu computador o Apollo Guidance Computer.
	Esse projeto sera implementado utilizando do código fonte 
	transcrito das anotações originais da linguagem assembly do Apollo 
	guidance computer. Assim implementando um assembler que leia 
	as 12 instruções da maquina e a microsintaxe que compõe o 
	codigo original. Simulando os periféricos e seus dados, a trajetória
	e a aterrisagem a lua. Isso sera implementado por um interface fisica
	fiel a interface original da maquina e comandado por um arduino UNO
	que ira se comunicar com um PC por meio da interface serial do 
	arduino. Assim podendo aparecer no PC o que esta acontecendo na simulação 
	contendo informação educacional, curiosidade, etc; A parte gráfica
	do projeto.
  
	
#IMPLEMENTAÇÃO DO PROJETO
	
	Interface Grafica
	Vai ser ter uma tela com informacao sobre os comandos a serem executados e uma renderizacao 3D da
	janela do landing module e do exterior, graficos e shader simples
	
	
	Interface Fisic	a
	A interface Fisica sera uma recriação fiel da interface do modulo do Apollo
	Guidance Computer dentro do modulo de comando ou seja a interface chamada de
	DSKY ou apelidada de "diskey"
	
		Essa interface tem 3 elementos 
		
		-Teclado numerico de 18 chaves	
			0-9 digitos	
			"+" 
			"-"
			VERB comandar que os próximos dois digitos que vão ser	
				digitados vão defenir uma ação
			NOUN comandar que os próximos dois digitas que vão ser
				digitados vão defenir um objeto da ação
			ENTRY avisar o computador que a entrada de input ja foi feita
			
			CLEAR deletar um erro do logging
			
			ERR RST Resetar o alarme de OPR ERR
			
			KEY REL Se o computador estar solicitando controle
				do display então a luz do KEY REL vai estar ligada			
					Ou seja o computador quer fazer o display de uma mensagem
					para isso ser feito o astronauta tem que apertar no 
					botao KEY REL
			PRO O programa sendo rodado pelo computador pode fazer uma requesição para fazer uma 
				ação por meio de mostrar a mensagem no KEY REL e se o astronauta 
				aprovar a ação como manusear o modulo lunar 
					PROG = 63
					VERB = 50
					NOUN = 18
				O astronauta aperta o botao PRO	

	
		-Display numerico
			Tem 3 áreas principais do display
				-VERB
					Ação sendo executada
				-NOUN
					Objeto da ação sendo executada
				-PROG	
					Programa sendo executado por exemplo na aterrisagem lunar
					isso seria o programa 63
		-Luzes de indicação
			KEY REL (Key Release) 
				O computador solicita o DISKY para mostrar uma informação importante
				ao astronauta
	
	O DISKY era operado utilizando de "verbs" e "nouns"
	como comandos. Onde o Verbo era a ação e o noun e o objeto
	da ação.
	
	Um exemplo de um comando seria "Display Velocidade"
	 
	Instruction Set:
		15 bit word size(não opera utilizando bytes como word)
		3bits para opcode
		12 bits para address
			
			primeiras 8 instruções , instruções basicas
			TC
				Transfer Control
				Basicament instrução jump
			CCS
				Count Compare and Skip
				Instrução de branching condicional
				O registro A foi carregado com valor especificado pela instrução
				
		
			INDEX
	
			XCH
		
			CS
	
			TS
	
			AD
			
			MASK
			
			instrucoes extracode
			SU
			
			MP
			
			DV
			

	O simulador em si vai ser uma maquina virtual do Apollo Guidance Computer, feita em C++
	implementando um assembler que leia a sintaxe da linguagem assembly original 
	do Apollo Guidance Computer. Completo com o proprio Scanner/Lexical Analyzer, Parser
	(reportar erros de sintaxe) e por fim diretamente par schedueling de instruções e registros sem 
	nenhuma otimização porém havera instruction schedueling e register schedueling pois o código da
	luminary apresenta instruções virtuais.
	
	Seria bom implementar um interpreter o qual vai fazer o papel de traduzir as instruções em tempo
	Nota que as instrucoes do luminary(programa que roda no AGC) é composto por instruções virtuais
	as quais implementam uma stack(estrutura de dados em pilha), vetores com indices,
	e operações de matrizes e vetores(vetores geometricos?) .O luminary em si é um pequeno sistema operacional
	em real time. 
	real podendo fazer o display para o usuário na tela do PC a memória,registros e branches do programa
	isso claro para um observador mais atento.
	O clock da simulação podera ser pausado para analizar esses detalhes;
	
	Como no computador real ele tera uma limitacao de 

	https://github.com/chrislgarry/Apollo-11
	


#PESQUISA:
	
	Palestra sobre o Apollo Guidance Computer
	
	https://www.youtube.com/watch?v=B1J2RMorJXM
	
	https://airandspace.si.edu/collection-objects/keyboard-display-dsky-apollo-guidance-computer/nasm_A19760744000	

	https://klabs.org/history/build_agc/build_agc_5.pdf
	
#COMO ESCREVER RESUMO:
	https://stricto.unama.br/pt-br/noticias/aprenda-fazer-um-resumo-impecavel
	
	-Resumo deve ser curto e objetvio
		
	-ESCRITO em terceira pessoa

	-Mensão ao autor que originou a obra
	
	-Usar aspas quando transcrever uma obra	
	
		-Apresentar idéia geral do artigo
		
		-Bases teoricas
