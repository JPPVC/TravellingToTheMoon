Apollo Guidance Computer Script 
vai ser uma linguagem interpretada, apesar disso sera typed

Para que?
Ferramenta de ensino assecivel para criancas e adolescente entenderem
logica computacional e programar o AGC.

Nota que una coisa interessante a se pensar
e que podera ser feita uma API para controlar o AGC assim 
rodase um scrip automatico para controlar a simulacao da nave
colocar isso em um joguinho multiplayer assim as criancas
vao ter que aprender conceitos de orbita computacao e trabalho em equipe 
para operar a nave ou batalhar com um ao outro 
e todo programa que utilizar de apenas 2KB de memoria
Tipos de Dados
	Vai ter os tipos de dados nativos ao AGC como tambem
	mais convenientes
	
	Nativos
	SP (single precision)	
		14 bits 
	DP (double precision)
		28bits
	TP (triple precision)
		42 bits
	Convenientes
	int -> (SP) 14 bits 
	
	uint -> unsigned int (SP) 15 bits

	long -> (DP) 28 bits
	
	ulong -> unsigned double
	
	num (numero)-> numero real SP 
		14 bits
	
	mnum (mega numero)-> numero real DP 
		28 bits	
	
	gnum (giga numero) -> numero real TP
		42 bits
	string ou texto(ponteiro de 10 bits para um caractere ASCII)
	
		

Palavras Chave

Controle de Fluxo 
	if ou se
		if (he == 1) terminal::print("Olá mundo");
		ou 
		se (he == 1) terminal::print("Olá mundo");
	while ou enqu
	
	else ou alem
		
	elif alse

Sintaxe para declaracao de variaveis e constantes
	
	const num hey = 0;
	
	num hey = 0;
	
	%a = hey; -> registro A (Acumulador) e igual a 0 ou seja 
	
Chamar uma rotina(funcao)
			
	nome_rotina(arg1, arg2, ...);
	
	const texto get = get_rotina("Ola mundo");

Estrutura de Dados
	Nao tera classes nem structs apenas apelidos
	que para usuarios avancados podem ser usados como structs
	
	typedef ou apelido
	
	apelido {gnum vel, string}
Rotinas
	
	tipo_dado nome_rotina(arg1, arg2,...) {
		...corpo...
	}

Macros (para usuarios avancados)
Pra escrever codigo
	@macro nome_macro (arg1, arg2) {
		...corpo...
	}

Nota que a funcao main nao e todo tipo de funcao que nao retornar nada 
tambem nao vai ter tipo de dado no inicio de sua declaracao

nota que os macros vao ser que nem macros do C arg1 vai ser apenas
um simbolo nao um tipo de dado que vai ser substituido na hora de compilacao
Outros
	# -> comentario
	
	@ -> prefixo para pre processor macros

	@carregar ou @import -> 
		@carregar "nome_biblioteca" 
EXEMPLO 
	....

	# Projeto GeAstro
	# Joao Pedro Protz Vicente
	#
	#
	#

	@carregar "dsky"
	@carregar "tela"
	@carregar "lum"
	
	main() {
		#enquanto o
		enq(lum::clock() == 1) {
			
			lum::vel vel = lum::velocidade();
			lum::alt =

			tela::print("Dado Do Modulo Lunar Apollo 11");
			tela::print(vel);
			tela::print(lum::altura());
				
			se ()	
		}	
	}
	
OUTPUT ESPERADO NA TELA DO PC 	
	
	Dado Do Modulo Lunar Apollo 11
	X m/h
	Y m
