module Contas where

-- Questão 1
-- Escreva uma função chamada filtrarContas que receba um Banco, um valor limite de Saldo e um TipoConta. Utilizando obrigatoriamente um gerador de lista
-- (list comprehension), a função deve retornar uma lista contendo apenas o Titular de todas as contas que possuam saldo maior ou igual ao limite fornecido 
-- e que sejam do tipo especificado.

baseContas :: Int -> (String, Float, String)
baseContas x
    | x == 1 = ("Ana",    100.0, "Corrente")
    | x == 2 = ("Bruno",  200.0, "Poupança")
    | x == 3 = ("Carla",  300.0, "Corrente")
    | x == 4 = ("Diego",  400.0, "Poupança")
    | x == 5 = ("Elena",  500.0, "Corrente")
    | otherwise = ("ninguem", 0.0, "nada")

type Titular = String
type Saldo = Float
type Tipo = String
type Conta = (Titular, Saldo, Tipo)
type Banco = [Conta]

criarContas :: Int -> Banco
criarContas x =
    if(x < 1) then []
    else if(x > 5) then criarContas (x - 1)
    else baseContas x : criarContas (x - 1)

filtrarContas :: Banco -> Saldo -> Tipo -> [Titular]
filtrarContas [] _ _ = []
filtrarContas titulares piso tipoConta = [nome | (nome, saldo, tipo) <- titulares, saldo >= piso && tipo == tipoConta]