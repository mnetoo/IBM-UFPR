module Vendas where

type Produto = String
type Preco = Float
type Venda = (Produto, Preco)

maisCaro :: [Venda] -> Venda
maisCaro [] = ("", 0.0)
maisCaro ((n, p):t)
    | p > precoAtual = (n, p)
    | otherwise = (nomeAtual, precoAtual)
    where
        (nomeAtual, precoAtual) = maisCaro t