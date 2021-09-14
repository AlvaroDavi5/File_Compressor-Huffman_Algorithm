# File_Compressor-Huffman_Algorithm

## Passo-a-Passo

- [ ] Ler endereço dos arquivos de texto e binários* que serão passados via linha de comando  
- [ ] Ler arquivo e iniciar o algoritmo  

#### ALGORITMO  
  1. Armazenar conteúdo do arquivo em uma lista encadeada onde cada nó contém os campos: valor, frequência, próximo, esquerda, direita  
  2. Excluir valores repetidos computando apenas a frequência e ordenar a lista por frequência (melhor ordem: crescente) ou criar vetor com o tamanho da tabela ASCII e incrementar posições frequêntes  
  3. Do início ao fim da lista, remover 2 nós e criar 1 novo nó cujos filhos são os dois removidos, reordenando a lista sempre que inserir o novo nó. Fazer isso recursivamente até restar apenas um elemento na lista, o "nó raiz" da árvore.  
  4. Pronta a árvore de codificação, apagar a lista sem apagar seus nós  
  5. Criar tabela de códigos e frequências, pode ser uma matriz MxN onde M = tamanho da tabela ASCII e N = altura da árvore +1  

- [ ] Codificar/Decodificar  
  > Salvar árvore no início do arquivo em notação pré-ordem  
