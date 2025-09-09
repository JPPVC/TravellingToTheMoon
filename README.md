
TRANSCREVER Versão final para o documento word no modelo SNEA

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

	Interface Fisica e Gráfica
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
	 

8	O simulador em si vai ser uma maquina virtual do Apollo Guidance Computer, feita em C++
	implementando um assembler que leia a sintaxe da linguagem assembly original 
	do Apollo Guidance Computer. Completo com o proprio Scanner/Lexical Analyzer, Parser
	(reportar erros de sintaxe) e por fim diretamente par schedueling de instruções e registros sem 
	nenhuma otimização pois além de ser desnecessario é preciso manter fidelidade.
	
	Seria bom implementar um interpreter o qual vai fazer o papel de traduzir as instruções em tempo
	real podendo fazer o display para o usuário na tela do PC a memória,registros e branches do programa
	isso claro para um observador mais atento.
	O clock da simulação podera ser pausado para analizar esses detalhes;
	

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
