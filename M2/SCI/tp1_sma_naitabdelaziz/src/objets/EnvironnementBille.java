/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package objets;

import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
import java.util.Observable;
import java.util.Observer;
import java.util.Random;

/**
 *
 * @author yanis
 */
public class EnvironnementBille extends Environnement{

   // private Environnement env;
    private Random r;
   // List<Observer> observers;
    int nbIterations;

    public EnvironnementBille(int width, int height, int nbBilles, int nbIter){
        super(width, height);
        int x, y;
        int depX, depY;
        Position p = null;
        Agent a = null;
        int deplacements[] = {0, -1, 1};

        r = new Random();
        nbIterations = nbIter;
        //env = new Environnement(width, height);
        //observers = new ArrayList<Observer>();

        for (int i = 0; i < nbBilles; i++) {
            do {
                x = r.nextInt(width);
                y = r.nextInt(height);
            } 
            while (estOccupee(x, y));

            depX = deplacements[r.nextInt(3)];
            depY = deplacements[r.nextInt(3)];

            p = new Position(x, y);
            p.setDepX(depX);
            p.setDepY(depY);
            
            System.out.println("DepX = "+ depX + " DepY = "+depY);

            a = new Bille(p);
            addAgent(a);           
        }
    }

    public void run() throws InterruptedException{    
        for (int i = 0; i < nbIterations; i++) {
           
            for (Agent a : getAgents()){
                Thread.sleep(1000);
                a.vivre(this); 
                
                //notifyObservers();
            }
            for(Observer o : observers){
                o.update(this, null);
            }
        }
    }
}
