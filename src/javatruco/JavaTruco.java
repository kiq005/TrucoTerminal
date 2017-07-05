/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package javatruco;

/**
 *
 * @author kaique
 */
public class JavaTruco {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        Jogo jogo = new Jogo(2);
        jogo.addJogador(new J_Humano());
        jogo.addJogador(new J_IA1());
        jogo.iniciar();
        
    }
    
}
