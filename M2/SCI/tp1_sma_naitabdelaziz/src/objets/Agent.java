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
public abstract class Agent {
    
    protected Position position;
    
    public Agent(){
    }
    
    public Agent(Position p){
        position = p;
    }
    
    public Position getPosition(){
        return position;
    }
    
    public void setPosition(Position p){
        position = p;
    }
    
    public abstract void vivre(Environnement e);
}
