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
public class Position {
    
    private int posX,posY,depX,depY;
    
    public Position(int x, int y){
        depX=0;
        depY=0;
        posX=x;
        posY=y;
    }
    
    public int getPosX(){
        return posX;
    }
    
    public int getPosY(){
        return posY;
    }
    
    public void setPosX(int _posX){
        posX=_posX;
    }
    
    public void setPosY(int _posY){
        posY=_posY;
    }
    
    public void setDepX(int x){
        depX=x;
    }
    
    public void setDepY(int y){
        depY=y;
    }
    
    public int getDepX(){
        return depX;
    }
    
    public int getDepY(){
        return depY;
    }
}
