/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package javatruco;

import java.util.Scanner;

/**
 *
 * @author kaique
 */
public class J_Humano extends Jogador{
    
    private Scanner teclado;
    
    public J_Humano(){
        super();
        teclado = new Scanner(System.in);
    }
    
    public void imprimeMao(){
        for(int i=0; i<this.cartas;i++){
            System.out.print(this.mao[i].Desenho() + " ");
        }
        System.out.print("\n");
    }

    @Override
    public Carta obterCarta() {
        Carta carta = null;
        int c;
        c = 0; 
        while(c<1 || c>this.cartas){
            System.out.println("Qual carta deseja jogar?[1-"+this.cartas+"]");
            imprimeMao();
            c = Integer.decode(teclado.nextLine());
        }
        
        carta = this.mao[c-1];
        this.mao[c-1]=null;
        this.cartas--;
        this.organizaMao();
        return carta;
    }
}
