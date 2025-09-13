

LINK para o documento oficial onde o resumo e info do projeto dever ser colocados até o dia 15/09
https://docs.google.com/document/d/1iXpttULFeAGEHqhbMUOEgKS-jvxk71JNAJrn8pi7_S0/edit?usp=sharing



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
	
	Nota que poderiamos pensar em integrar nosso projeto com o projeto yaAGC o qual 
	é um emulador do Apollo Guidance Computer escrito em C. 
	
	Limite máximo do computador
	"38,912 15-bit" word e 1 bit reservado para deteção de erros 
	disponivel apenas para o hardware.

	"36K of core rope and 2K of RAM"
			
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
	luminary apresenta instruções virtuais. Essas instruções chamadas de virtuais 
	eram aquelas instruções as quais eram chamada de interpreter language e a lingua que compõe 
	o instruction set da maquina em si é chamada de basic language.
 	
	O compilador/assembler do AGC era chamado de YUL originalmente (yuletide) e depois dado o nome
	de General Assembler Program "GAP". Daria para implementar o YUL praticamente como ele foi implementado
	originalmente por haver documentação dos "padrões de programação" utilizados durante o projeto.

	No projeto original se utilizava de um debugger que guardava codigo em punchcards e tape rolls que era carregado 
	na memória do AGC, nota que a capacidade do AGC 
	de carregar binarios para memória em runtime é extremamente 
	limitada. Nota que a storage do binario do luminary que foi para as missões era 100% ROM
	ja que os fios literalmente foram "costurados" as chamadas core ropes dentro das portas NOR.
	
	O YUL foi originalmente feito para rodar em um IBM 650 porém foi rapidamente portado para 
	O Honeywell 800 devido a limitações do de antes.
	
	Seria bom implementar um interpreter o qual vai fazer o papel de traduzir as instruções em tempo
	Nota que as instrucoes do luminary(programa que roda no AGC) é composto por instruções virtuais
	as quais implementam uma stack(estrutura de dados em pilha), vetores com indices,
	e operações de matrizes e vetores(vetores geometricos?) .O luminary em si é um pequeno sistema operacional
	em real time. 
	real podendo fazer o display para o usuário na tela do PC a memória,registros e branches do programa
	isso claro para um observador mais atento.
	O clock da simulação podera ser pausado para analizar esses detalhes;
	
	As Instruções do AGC e representação de dados
	
	Naquela época não existia o famos floating point IEE 754, standard para representação de números,
	"reais". o AGC tinha seu próprio método, o que incluia um zero negativo e positivo (que divertido)
	A maioria das operações eram feitas utilizando o "SP" Single Precision data type, variante de 1's complement notation
		
		111111111111111 -> -0
		000000000000000 -> +0 
	


	Código fonte
		Um código fonte do luminary por exemplo mistura tanto instruções virtuais(interpreter language)
		quanto instruções de assembly(basic language).
		
		-Formatação
			código fonte codificad em ASCII
			
			Linhas nulas são ignoradas
			
			# commentario, nota que no YUL (difere do yaYUL) o codigo fonte era em punch cards
			não se sabe ao certo como comentario eram definidos porém era algo aver com as
			colunas do punchcard
			
			$ atua como o pre processor macro #include do C isso para compatibilidade
			com a versão digital do código do Luminary encontrado no github, nem existia
			arquivos nos sistemas em que rodava YUL

			Nomes para constantes definidas pelo programador seriam de 8 caracteres ou 
			menos na primeira coluna e não podiam incluir # ou começar em $,
			exemplo valido -> "-1/(D)+A"
			
			 
						
	https://github.com/chrislgarry/Apollo-11
	
#PERGUNTAS
	Porque o luminary(Programa principal do AGC) não foi escrito estritamente em AGC assembly(basic language)?
	O principal problema está em como a memória de programa do luminary era guardada. Era utilizado de portas NOR
	e "core ropes". Ou seja o programa era costurado dentro da memória do AGC. O que demandava tempo e trabalho
	manual, tanto que esse tipo de memória foi chamada de LOL (Little Old Ladies). Ou seja programar tudo 
	em instruções simples demanda armazenamento além de até naquela época ser difficil de gerenciar enquanto se 
	escreve o projeto. Assim o compilador/assembler utilizado chamado de YUL e depois chamadado de GAP, os quais 
	rodaram originalmente em um IBM 650 e depois migrados para um Honeywell 800. Foi introduzido dentro do AGC
	Assim tendo instruções virtuais que traduzidas pelo interpreter.

	Qual é a differença entre o YUL e yaYUL?
	O YUL ele era um compilador/assembler original que rodava na core memories do AGC e tabem no IBM 650 e depois 
	no Honeywwll 800. Ele foi programado com uma mistura de linguas uma de alto nive e outra de baixo inventadas no MIT
	YUL foi no futuro substituido pelo GAP, General Assembler Programm. 
	Enquanto que o yaYUL é um programa escrito em C que emula o YUL original	
	
#PESQUISA:
	
	Palestra sobre o Apollo Guidance Computer
	
	https://www.youtube.com/watch?v=B1J2RMorJXM
	
	https://airandspace.si.edu/collection-objects/keyboard-display-dsky-apollo-guidance-computer/nasm_A19760744000	

	https://klabs.org/history/build_agc/build_agc_5.pdf

	https://www.ibiblio.org/apollo/assembly_language_manual.html
	
	https://github.com/virtualagc/virtualagc
		
	https://www.ibiblio.org/apollo/yaYUL.html#gsc.tab=0

		https://www.ibiblio.org/apollo/yaAGC.html#gsc.tab=0    (LER ISSO)
#COMO ESCREVER RESUMO:
	https://stricto.unama.br/pt-br/noticias/aprenda-fazer-um-resumo-impecavel
	
	-Resumo deve ser curto e objetvio
		
	-ESCRITO em terceira pessoa

	-Mensão ao autor que originou a obra
	
	-Usar aspas quando transcrever uma obra	
	
		-Apresentar idéia geral do artigo
		
		-Bases teoricas




#PESQUISA E IMPLEMENTACAO DO YAYUL
	O que é o yaYUL
	
	#PESQUISA AGC ASSEMBLY
	Dados
		bit order
		
			Parity bits e parity errors
		
		Single Precision
	
		Double Precision
		
		Triple Precision
		
		Vetores Geometricos 3D
	
		Para acessar uma word da memoria isso leva 12 microsegundos
		ou um ciclo lembrando que a word e 15 bits 
		onde o decimo sexto bit e o parity bit utilizado
		para detectar parity errors
		os quais acontecem quando um numero par de bits igual a 1
		sao detectados pelo computador
	
		Instrucoes
		3 bit opcode para 8 instrucoes
		quarter codes sao uma extensao dos opcodes originais
		onde sao utilizados 5bits.	
			em uma instrucao normal 12 bits sao utilizadas
			formando 4096 locais de memoria decimais
			ou 0-7777 octal isso e combinado com o Bank Register 
			permitindo enderecamento de 15 bits o Super Bank Bit 
			permite 16 bits
		Memoria
		0-3777 octal e memoria apagavel(nao se usa o termo RAM)
		10000-117777 octal e a memoria fixa a memoria programada
		pelas core ropes
		
		concluise que o programador tem apenas 2048 locais decimais
		de memoria modificavel 2KB(pouco até para época)
	
			Na memoria apagavel bits 12 e 11 sao 0
			para falar para o HW que e memoria apagavel	
			assim tendo 10 bits para memoria apagavel
