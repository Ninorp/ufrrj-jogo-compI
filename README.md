# ufrrj-jogo-compI
Jogo em C com a lib SDL para Comp I

# HISTÓRIA E MANUAL DE INSTALAÇÃO
História.
				TowerCraft,e as Tábuas de Presselia


Essa história se passa em tempos antigos, tão antigos que nem se imaginava a divisão do mundo como a atual. Onde a raça dos Darkin’s estava dominando o mundo inteiro impondo seus desejos com o seu poder quase absoluto. Mas uma raça estava predestinada a interromper tal domínio, a raça dos Sithmas.
Os Darkin’s eram uma raça de muita força e brutalidade, vivendo para lutar e lutando para viver, demonstrando todas as suas capacidades de lutas e sua sede por sangue em cada uma delas. Já os Sithmas estavam quase em extinção, devido ao sua baixa capacidade de luta, eles sempre se esconderam através dos tempos para conseguirem sobreviver a qualquer tipo de desastre, mas eles nunca ficaram parados,sempre estudaram escondidos e acumularam recursos para se defender se necessário.
Muitos dos Darkin’s queriam encontrar e acabar com os Sithmas, por conta da antiga escritura sobre as Tábuas de Pressellia, os Sithmas estavam predestinados a salvar o mundo de algo ou alguém que possa interromper a paz que nele existe. Presséllia era um lugar obscuro e destruído após tantas guerras, nem mesmo um lugar sagrado foi preservado pelos Darkin’s, que passaram por cima de tudo atrás dessas escrituras.
Os Sithmas sempre tiveram o conhecimento sobre a tal escritura, porém nunca acreditaram que algum momento eles deveriam salvar o mundo de algum mal,principalmente o tal “escolhido” das Tábuas de Presselia, e seu nome era Crowhard. 
Apesar das escrituras, Crowhard não acreditava que ele sozinho iria guiar os Sithmas até a glória de vencer os Darkin’s em um confronto direto, pois ele sabia que comparado aos Darkin’s , eles eram muito inferiores em questão de força e poder. Porém com o apoio de sua amada Miss Vitsse, ele acreditará que talvez haja a possibilidade deles vencerem um confronto direto… Se eles usarem o ponto mais forte de sua raça, a inteligência.
	A inteligência dos Sithmas era tão aguçada que eles sempre se destacaram em estratégia e avanço tecnológico, mas não conseguiram avançar em questões fisicas, não possuíam um grande poderio em combate corpo a corpo, a única de chance deles vencerem os perversos Darkin’s, é utilizando as suas armas mais poderosas e evitando o combate direto. Sabendo disso, Crowhard inventou uma espécie de máquina que consegue protegê-los e atacarem ao mesmo tempo… As suas torres. Torres essas que, usadas de maneira correta,  conseguem impedir e destruir qualquer tipo de avanço por parte dos Darkin’s. 
Com isso se desenha uma batalha feroz entre os Sithmas e os Darkin’s, mas principalmente entre o escolhido e principal esperança pelo lado dos Sithmas, o Crowhard, contra o líder dos Darkin’s, Kayen “O conquistador”...Será que o nosso herói conseguirá vencer a sua insegurança e a de seu povo,liderá-los contra os Darkin’s e com isso salvar o mundo de Khankim, cumprindo assim a escrita das Tábuas de Presselia  ou será que Kayen e seus comandados  o impedirão, mantendo assim seu reinado de tirania e maldade sobre o mundo...Essas são perguntas ainda sem respostas, mas de que lado você está ? Dos inteligentes, porém frágeis, Sithmas de Crowhard ou do lado dos tiranos Darkin’s e ser comando por Kayen?  Independente da escolha uma coisa é certa… O mundo de Khankim jamais será o mesmo….


Como compilar

Para rodar o programa é necessário ter o SDL2 e o GCC instalados no seu computador. Se já houver esses dois programas instalados, abra seu terminal e utilize o comando abaixo e digite:  .\TowerCraft 

COMANDO

PARA WINDOWS:

  gcc -o TowerCraft TowerCraft.c -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf 


PARA LINUX:

  gcc -o TowerCraft TowerCraft.c -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf

Caso não tenha o SDL2 instalado em sua máquina digite os seguintes comandos abaixo em seu terminal NA MESMA ORDEM: 

  sudo apt-get install libsdl2-2.0

  sudo apt-get install libsdl2-dev

Caso não o senhor(a) não possua o GCC digite os seguintes codigos também EM ORDEM em seu terminal:

  sudo apt-get install python-software-properties

  sudo apt-get update
  
	sudo apt-get install gcc-4.8
  
	sudo update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-4.8 50








