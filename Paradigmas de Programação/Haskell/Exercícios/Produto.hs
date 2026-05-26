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