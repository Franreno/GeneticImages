# Genetic Images

O projeto tem como objetivo desenvolver um algoritmo genético capaz de reproduzir uma imagem
que lhe foi dada. ,

A imagem utilizada é do formato `.pgm` no padrão `P5`. Este formato é um arquivo binário que descreve uma imagem em escalas de cinza, com cada byte variando de 0 a 255.


## Motivação

Geração de imagens procedurais através de algoritmos evolutivos. Um bom artigo que introduz a ideia é o apresentado no [link](https://shahriyarshahrabi.medium.com/procedural-paintings-with-genetic-evolution-algorithm-6838a6e64703).


## Implemetação

O algoritmo foi desenvolvido utilizando a linguagem `C++`, juntamente com a biblioteca `OpenGL`.

No algoritmo evolutivo, foram implementados métodos que avaliavam diferentes combinações de seleção e rearranjo da população, o que permitiu uma comparação entre os métodos para o problema proposto. Tais implementações envolviam:

- **Elitismo**:
  - juntamente com mutação variável e genocídio.
  - juntamente com mutação variável e predação randômica.
  - juntamente com mutação variável e predação sintética.
  - juntamente com mutação variável e uma combinação qualquer entre os 3 métodos de rearranjo propostos.
- **Torneio**:
  - juntamente com mutação variável e genocídio.
  - juntamente com mutação variável e predação randômica.
  - juntamente com mutação variável e predação sintética.
  - juntamente com mutação variável e uma combinação qualquer entre os 3 métodos de rearranjo propostos.


## Resultados Obtidos

Com a execução do algoritmo, imagens similares a este:


<table>
    <tr>
        <th><center>Imagem Original</center></th>
        <th><center>Imagem Construída</center></th> 
    </tr>
    <tr>
        <td><img src="https://github.com/Franreno/GeneticImages/blob/main/data/Original.png?raw=true" raw=true width=250></td>
        <td><img src="https://github.com/Franreno/GeneticImages/blob/main/data/torneio3.png?raw=true" raw=true width=250></td>
    </tr>
</table>


## Instalação


### Requisitos

Para reproduzir o programa é necessário ter instalado:

- Make
- C11++
- Glut/OpenGL