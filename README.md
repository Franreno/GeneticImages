# Genetic Images

![C++](https://img.shields.io/badge/-C++-333333?style=flat&logo=cplusplus)
![OpenGL](https://img.shields.io/badge/-OpenGL-333333?style=flat&logo=opengl)
![Python](https://img.shields.io/badge/-Matplotlib-333333?style=flat&logo=python)


O projeto tem como objetivo desenvolver um algoritmo genético capaz de reproduzir uma imagem que lhe foi dada.

A imagem utilizada é do formato `.pgm` no padrão `P5`. Este formato é um arquivo binário que descreve uma imagem em escalas de cinza, com cada byte variando de 0 a 255.

Este projeto foi desenvolvido na disciplina [SCC0713](https://gitlab.com/simoesusp/disciplinas/-/tree/master/SSC0713-Sistemas-Evolutivos-Aplicados-a-Robotica) e possui apenas fins educacionais. 

Link da apresentação: [clique aqui](https://drive.google.com/file/d/1YB37n-Ap4GNE1A4_iPlwJDlpG-54Z65l/view?usp=sharing).

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
        <td><img src="https://github.com/Franreno/GeneticImages/blob/main/Graficos/FotoOriginalUtilizadaNosGraficos.png?raw=true" raw=true width=250></td>
        <td><img src="https://github.com/Franreno/GeneticImages/blob/main/Graficos/torneio/torneio3/torneio3.png?raw=true" raw=true width=250></td>
    </tr>
</table>

### Comparação entre os algoritmos utilitizando `Elitismo`

Para cada estratégia diferente de Elitismo, tem-se que:

- `elitismo0`: Elitismo + mutação variável + genocídio.
- `elitismo1`: Elitismo + mutação variável + predação randômica.
- `elitismo2`: Elitismo + mutação variável + predação randômica + genocídio.
- `elitismo3`: Elitismo + mutação variável + predação sintética.
- `elitismo4`: Elitismo + mutação variável + predação sintética + genocídio.
- `elitismo5`: Elitismo + mutação variável + predação randômica + predação sintética.
- `elitismo6`: Elitismo + mutação variável +  predação randômica + predação sintética + genocídio.

As comparações entre os melhores de todos foram construídas em um gráfico de gerações por fitness:

<img src="https://github.com/Franreno/GeneticImages/blob/main/Graficos/SoElitismo.png?raw=true" raw=true>

Os gráficos contendo a comparação entre o melhor de todos e a média populacional para cada estratégia podem ser observados na pasta [Gráficos](https://github.com/Franreno/GeneticImages/tree/main/Graficos).

### Comparação entre os algoritmos utilitizando `Torneio`

Para cada estratégia diferente de Torneio, tem-se que:

- `torneio0`: Torneio + mutação variável + genocídio.
- `torneio1`: Torneio + mutação variável + predação randômica.
- `torneio2`: Torneio + mutação variável + predação randômica + genocídio.
- `torneio3`: Torneio + mutação variável + predação sintética.
- `torneio4`: Torneio + mutação variável + predação sintética + genocídio.
- `torneio5`: Torneio + mutação variável + predação randômica + predação sintética.
- `torneio6`: Torneio + mutação variável +  predação randômica + predação sintética + genocídio.

As comparações entre os melhores de todos foram construídas em um gráfico de gerações por fitness:

<img src="https://github.com/Franreno/GeneticImages/blob/main/Graficos/soTorneio.png?raw=true" raw=true>

Os gráficos contendo a comparação entre o melhor de todos e a média populacional para cada estratégia podem ser observados na pasta [Gráficos](https://github.com/Franreno/GeneticImages/tree/main/Graficos).

### Comparação entre todas as estratégias utilizadas.

Pode-se comparar as estratégias utilizadas por meio de um gráfico comparativo entre o melhor de todos para cada estratégia. O gráfico de gerações por fitness é:

<img src="https://github.com/Franreno/GeneticImages/blob/main/Graficos/Todas.png?raw=true" raw=true>



## Rodando em uma imagem de tamanho 100x100

O algoritmo rodou por 1 hora e meia, utilizando a estratégia do torneio3, em uma imagem de 100x100 pixels atingindo um fitness satisfatório de 8985.7/10000.

<table>
    <tr>
        <th><center>Imagem Original</center></th>
        <th><center>Imagem Construída</center></th> 
    </tr>
    <tr>
        <td><img src="https://github.com/Franreno/GeneticImages/blob/main/Graficos/100x100/100x100_Original_pgm.png?raw=true" raw=true width=250></td>
        <td><img src="https://github.com/Franreno/GeneticImages/blob/main/Graficos/100x100/100x100.jpeg?raw=true" raw=true width=250></td>
    </tr>
</table>

### Gráfico da imagem 100x100
<img src="https://github.com/Franreno/GeneticImages/blob/main/Graficos/100x100/100x100_Original.png?raw=true" raw=true>



## Instalação


### Requisitos

Para reproduzir o programa é necessário ter instalado:

- Make
- C11++
- Glut/OpenGL

### Execução

Para executar, basta executar os comandos abaixo na pasta do projeto:

```
  make all
  make run
```

## Autores

- [@DanArrays](https://www.github.com/DanArrays)
- [@franreno](https://www.github.com/franreno)
- [@rafaeldschultz](https://www.github.com/rafaeldschultz)
