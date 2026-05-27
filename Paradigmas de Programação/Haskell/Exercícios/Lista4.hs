module Lista4 where


--  Dada uma tupla do tipo (String, String, Char), escreva três funções diferentes para retornar cada elemento da tupla.
leNome :: (String, String, Char) -> String
leNome (nome, _, _) = nome

leGraduacao :: (String, String, Char) -> String
leGraduacao (_, graduacao, _) = graduacao

leGenero :: (String, String, Char) -> Char
leGenero (_, _, genero) = genero

-- -----------------------------------------------------------------

base :: Int -> (String, String, Char)
base x
    |x == 1 = ("joao", "mestre", 'm')
    |x == 2 = ("jonas", "doutor", 'm')
    |x == 3 = ("joice", "mestre", 'f')
    |x == 4 = ("janete", "doutor", 'f')
    |x == 5 = ("jose", "mestre", 'm')
    |otherwise = ("ninguem", "nada", 'x')

-- a) Escreva uma função recursiva contMestre que retorne o número de mestres.
contMestre :: Int -> Int
contMestre x
    | x < 1 = 0
    | leGraduacao (base x) == "mestre" = 1 + contMestre (x - 1)
    | otherwise = contMestre(x - 1)


-- b) Escreva uma função recursiva contDoc que retorne o número de doutores.
contDoutor :: Int -> Int
contDoutor x
    | x < 1 = 0
    | leGraduacao (base x) == "doutor" = 1 + contDoutor (x - 1)
    | otherwise = contDoutor(x - 1)

-- c) Transforme as funções desenvolvidas nos itens a) e b) em uma única função contMD, passando a titulação como parâmetro.
contMD :: Int -> String -> Int
contMD x graduacao = 
    if(x < 1) then 0
    else if(graduacao == "doutor") then 
        if(leGraduacao (base x) == "doutor") then 1 + contMD (x - 1) graduacao
        else contMD (x - 1) graduacao
    else 
        if(leGraduacao (base x) == "mestre") then 1 + contMD (x - 1) graduacao
        else contMD (x - 1) graduacao

-- d) Crie uma nova função cont adicionando a função desenvolvida no item c) o gênero como parâmetro (f: feminio ou m: masculino).
cont :: Int -> String -> Char -> Int
cont x graduacao genero
    | x < 1 = 0
    | leGraduacao (base x) == graduacao && leGenero (base x) == genero = 1 + cont (x - 1) graduacao genero
    | otherwise = cont (x - 1) graduacao genero

-- -----------------------------------------------------------------

-- a) Crie um apelido para o tipo de elementos da tupla (nome, titulo, gênero), para a
-- tupla (pesquisador) e para a lista de pesquisadores (grupo). Para isso, utilize a
-- palavra-chave type.

type NomePesq = String
type GraduacaoPesq = String
type GeneroPesq = Char
type Pesquisador = (NomePesq, GraduacaoPesq, GeneroPesq)
type Pesquisadores = [Pesquisador]

-- b) Crie uma função recursiva para formar uma lista de pesquisadores com os elementos da função base.
listaPesquisadores :: Int -> Pesquisadores
listaPesquisadores x
    | x < 1 = []
    | x <= 5 = base x : listaPesquisadores (x - 1)
    | otherwise = listaPesquisadores (x - 1)

-- c) Escreva uma função que receba uma lista de pesquisadores e retorne outra lista
-- apenas com o nome de todos os pesquisadores que possuem o título de doutor.
-- Utilize o gerador de lista.
listaDoutores :: Pesquisadores -> [NomePesq]
listaDoutores [] = []
listaDoutores lista = [nome | (nome, graduacao, genero) <- lista, graduacao == "doutor"]

listaMestre :: Pesquisadores -> [NomePesq]
listaMestre [] = []
listaMestre lista = [nome | (nome, graduacao, genero) <- lista, graduacao == "mestre"]

-- -----------------------------------------------------------------

-- 4) Crie um módulo para armazenar as funções de tratamento abaixo:
-- a) Uma função que receba um nome e adicione no início o termo “Sr.”
addSr :: String -> String
addSr nome = "Sr. " ++ nome

-- b) Uma função que receba um nome e adicione no início o termo “Sra.”
addSra :: String -> String
addSra nome = "Sra. " ++ nome

-- c) Uma função que receba um nome e adicione no início o termo “Srta.”
addSrta :: String -> String
addSrta nome = "Srta. " ++ nome

-- d) Uma função recursiva de alta ordem (do tipo mapeamento) que receba uma lista de
-- nomes e uma das funções definidas em (a), (b) ou (c). Essa função deve retornar
-- uma lista de nome com a adição do termo de tratamento no início.
addTratamento :: (String -> String) -> [String] -> [String]
addTratamento _ [] = []
addTratamento f (h:t) = (f h) : (addTratamento f t)

-- -----------------------------------------------------------------

-- 5) Crie um módulo para armazenar as funções abaixo:
-- a) Uma função que receba um valor real e verifique se é positivo.
positivo :: Int -> Bool
positivo x
    | x > 0 = True
    | otherwise = False

-- b) Uma função que receba um valor real e verifique se é negativo.
negativo :: Int -> Bool
negativo x
    | x < 0 = True
    | otherwise = False

-- c) Uma função que receba um valor real e verifique se é igual a zero.
zero :: Int -> Bool
zero x
    | x == 0 = True
    | otherwise = False

-- d) Uma função recursiva de alta ordem (do tipo filtro) que receba uma lista de valores
-- e permita selecionar os elementos que satisfazem as condições (a), (b) ou (c).
verificaNumero :: (Int -> Bool) -> [Int] -> [Int]
verificaNumero _ [] = []
verificaNumero f (h:t)
    | (f h) == True = h : (verificaNumero f t)
    | otherwise = verificaNumero f t

-- -----------------------------------------------------------------