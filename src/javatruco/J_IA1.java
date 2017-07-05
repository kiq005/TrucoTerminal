/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package javatruco;

import static java.lang.Math.random;

/**
 *
 * @author kaique
 */
public class J_IA1 extends Jogador{
    
    
    
    public J_IA1(){
        super();
    }

    @Override
    public Carta obterCarta() {
        if(cartas<1)
            return null;
        int selecao = (int) random()*(this.cartas-1);
        Carta carta = this.mao[selecao];
        this.mao[selecao]=null;
        this.cartas--;
        this.organizaMao();
        System.out.println("IA jogou carta: " + carta.Desenho());
        return carta;
    }
}
