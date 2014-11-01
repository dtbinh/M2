/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

package objets;

import java.awt.Button;
import java.awt.Color;
import java.awt.Graphics;
import java.awt.GridLayout;
import java.util.Observable;
import java.util.Observer;
import javax.swing.JFrame;
import javax.swing.JPanel;

/**
 *
 * @author yanis
 */
public class GuiParticules implements Observer{

    private Environnement environnement;
    private JFrame window;
    private JPanel pane;
    
    public GuiParticules(Environnement e){
        environnement = e;
        e.addObserver(this);
        /*window = new JFrame("Particules");
        window.setSize(500, 500);
        window.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        window.add(pane);
        window.setVisible(true);*/
    }
    
    public void affiche(){
        
        for(int i=0;i<environnement.getHeight();i++){
            for(int j=0;j<environnement.getWidth();j++){
                System.out.print("|");
                if(environnement.estOccupee(j, i)){
                    System.out.print("0");
                }
                else{
                    System.out.print(" ");
                }
            }
            System.out.println();
        }
    }
    
    @Override
    public void update(Observable o, Object o1) {
        affiche();
    }
    
}
