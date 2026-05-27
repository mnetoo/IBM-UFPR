module Produto where

-- Exercício 1

baseProduto :: Int -> (String, Float, Int)
baseProduto x
    | x == 1 = ("notebook", 3500.0, 10)
    | x == 2 = ("mouse", 150.0, 50)
    | x == 3 = ("teclado", 200.0, 30)
    | x == 4 = ("monitor", 1800.0, 5)
    | x == 5 = ("headset", 400.0, 20)
    | otherwise = ("nenhum", 0.0, 0)

-- a) Crie apelidos de tipo com type para Nome, Preco, Estoque, Produto e Catalogo.
type NomeProduto = String
type PrecoProduto = Float
type QuantidadeProduto = Int
type EstoqueProduto = Int
type Produto = (NomeProduto, PrecoProduto, QuantidadeProduto)
type Catalogo = [Produto]

-- b) Crie uma função recursiva para formar uma lista de produtos com os elementos da função base.
criaCatalogo :: Int -> Catalogo
criaCatalogo x
    | x < 1 = []
    | x > 5 = criaCatalogo (x - 1)
    | otherwise = baseProduto x : criaCatalogo (x - 1)

-- c) Escreva uma função recursiva totalEstoque que receba um Catalogo e retorne o valor total em estoque 
-- (preço × quantidade) de todos os produtos.
totalEstoque :: Catalogo -> Float
totalEstoque [] = 0.0
totalEstoque ((_, preco, quantidade):t)
    | quantidade > 0 = (preco * fromIntegral quantidade) + totalEstoque t
    | otherwise = totalEstoque t

-- d) Escreva uma função produtosBaratos que receba um Catalogo e um limite de preço, e retorne usando
-- gerador de lista apenas os nomes dos produtos com preço abaixo do limite.
produtosBaratos :: Catalogo -> PrecoProduto -> [NomeProduto]
produtosBaratos catalogo pmax = [nome | (nome, preco, _) <- catalogo, preco <= pmax]

-- -------------------------------------------------------------------------------------------------------

-- c) Escreva uma função recursiva removerEsgotados :: [Produto] -> [Produto] que remova da lista todos os 
-- produtos cuja quantidade seja zero.
removerEsgotados :: Catalogo -> Catalogo
removerEsgotados [] = []
removerEsgotados ((nome, preco, quantidade):t)
    | quantidade > 0 = (nome, preco, quantidade) : removerEsgotados t
    | otherwise = removerEsgotados t 

-- d) Escreva uma função recursiva aplicarDesconto :: Double -> [Produto] -> [Produto] que receba um percentual 
-- (ex.: 0.10 para 10%) e retorne a lista com o preço de todos os produtos reduzido por esse percentual.

-- Com função de alta ordem
desconto :: PrecoProduto -> PrecoProduto
desconto x = x - (x * 0.10)

aplicarDesconto :: Catalogo -> (PrecoProduto -> PrecoProduto) -> Catalogo
aplicarDesconto [] _ = []
aplicarDesconto ((nome, preco, quantidade):t) f = (nome, f preco, quantidade) : aplicarDesconto t f 

-- Sem função de alta ordem
aplicarDesconto2 :: Catalogo -> Catalogo
aplicarDesconto2 [] = []
aplicarDesconto2 ((nome, preco, quantidade):t)= (nome, preco - (preco * 0.10), quantidade) : aplicarDesconto2 t