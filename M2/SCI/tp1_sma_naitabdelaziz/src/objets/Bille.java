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
public class Bille extends Agent{
    
    public Bille(Position p){
        super(p);
    }
    
    public void vivre(Environnement e){
        int currentX = position.getPosX();
        int currentY = position.getPosY();
        
        int newX, newY;
        
        if(currentX==0){
            position.setDepX(1);
        }
            
        if(currentX==e.getWidth()-1)
            position.setDepX(-1);
        if(currentY==0)
            position.setDepY(1);
        if(currentY==e.getHeight()-1)
            position.setDepY(-1);
        
        newX = position.getPosX()+position.getDepX();
        newY = position.getPosY()+position.getDepY();
        
        position.setPosX(newX);
        position.setPosY(newY);
        
        e.liberer(currentX, currentY);
        e.occuper(newX, newY);
    }   
}
