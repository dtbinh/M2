/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

package objets;

/**
 *
 * @author yanis
 */
public class Requin extends Agent {
    private boolean vivant;
    private static int tempsGestation = 10;
    private static int tempsMort = 3;
    private int cptGestation;
    private int cptNourriture;
    
    public Requin(Position p){
        super(p);
        vivant = true;
        cptGestation = 0;
        cptNourriture = 0;
    }
    
    
    

    @Override
    public void vivre(Environnement e) {
        int posX = position.getPosX();
        int posY = position.getPosY();
        
        
        
        
                
    }
    
}
