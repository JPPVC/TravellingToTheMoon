
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
	Guidance Computer dentro do modulo de comando 

	O simulador em si vai ser uma maquina virtual do Apollo Guidance Computer, feita em C++
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
		

#COMO ESCREVER RESUMO:
	https://stricto.unama.br/pt-br/noticias/aprenda-fazer-um-resumo-impecavel
	
	-Resumo deve ser curto e objetvio
		
	-ESCRITO em terceira pessoa

	-Mensão ao autor que originou a obra
	
	-Usar aspas quando transcrever uma obra	
	
		-Apresentar idéia geral do artigo
		
		-Bases teoricas
