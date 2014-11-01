/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

package test;


import objets.EnvironnementBille;
import objets.GuiParticules;

/**
 *
 * @author yanis
 */
public class Main {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) throws InterruptedException{
        EnvironnementBille jeu = new EnvironnementBille(5, 5,1,100000); 
        GuiParticules gui = new GuiParticules(jeu);
        jeu.run();    
    }
    
}
