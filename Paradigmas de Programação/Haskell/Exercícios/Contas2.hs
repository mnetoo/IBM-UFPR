module Contas2 where

-- a) Utilize type para criar os apelidos Titular, Tipo, Valor e Transacao.
type TitularConta = String
type TipoConta = String
type ValorConta = Float
type TransacaoConta = (TitularConta, TipoConta, ValorConta)

-- b) Escreva uma função recursiva saldoFinal :: Titular -> [Transacao] -> Double que calcule o saldo final de um titular, 
-- somando depósitos e subtraindo saques. Transações de outros titulares devem ser ignoradas.
saldoFinal :: TitularConta -> [TransacaoConta] -> ValorConta
saldoFinal _ [] = 0.0
saldoFinal tit ((nome, tipo, valor):t)
    | nome == tit && tipo == "saque" = valor + saldoFinal tit t
    | nome == tit && tipo == "deposito" = (-valor) + saldoFinal tit t
    | otherwise = saldoFinal tit t

-- c) Escreva uma função recursiva maiorDeposito :: Titular -> [Transacao] -> Double que retorne o valor do maior depósito feito por
-- um titular. Assuma que existe ao menos um depósito para o titular informado.
maiorDeposito :: Titular -> [TransacaoConta] -> Double
maiorDeposito _ [] = 0.0
maiorDeposito tit ((nome, tipo, valor):t)
    | depositoTitular && valor > maiorCauda = valor
    | otherwise = maiorCauda
    where
        depositoTitular = nome == tit && tipo == "deposito"
        maiorCauda = maiorDeposito tit t

-- d) Escreva uma função recursiva contarSaques :: [Transacao] -> Int que conte o total de saques de todos os titulares.
contarSaques :: [TransacaoConta] -> Int
contarSaques [] = 0
contarSaques ((_, tipo, valor):t)
    | tipo == "saque" = 1 + contarSaques t
    | otherwise = contarSaques t

-- e) Escreva uma função recursiva de alta ordem aplicarTaxa :: (Valor -> Valor) -> Tipo -> [Transacao] -> [Transacao] que receba uma função 
-- de transformação, um tipo de transação, e aplique a transformação apenas nas transações daquele tipo, retornando a lista completa atualizada.
juros :: ValorConta -> ValorConta
juros x = x + (x * 0.98)

aplicarTaxa :: (ValorConta -> ValorConta) -> TipoConta -> [TransacaoConta] -> [TransacaoConta]
aplicarTaxa _ _ [] = []
aplicarTaxa f tip ((nome, tipo, valor):t)
    | tipo == tip = (nome, tipo, f valor) : aplicarTaxa f tip t
    | otherwise (nome, tipo, f valaor) : aplicarTaxa f tip t