/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

package objets;

import java.util.ArrayList;
import java.util.List;
import java.util.Observable;
import java.util.Observer;
import java.util.Random;

/**
 *
 * @author yanis
 */
public class Environnement extends Observable{
    
    protected int width,height;
    protected int nbAgents;
    
    protected List<Agent> agents;
    protected boolean[][] grille;
    protected List<Observer> observers;
    
    public Environnement(int width,int height){
        nbAgents=0;
        this.width = width;
        this.height= height;
        grille = new boolean[height][width];
        for(int i=0;i<height;i++){
            for(int j=0;j<width;j++){
                grille[i][j]=false;
            }
        }
        agents = new ArrayList<Agent>();   
        observers = new ArrayList<Observer>();
    }
    
    public int getNbAgents(){
        return agents.size();
    }
    
    public int getHeight(){
        return height;
    }
    
    public int getWidth(){
        return width;
    }
    
    public List<Agent> getAgents(){
        return agents;
    }
    
    public void addAgent(Agent agent){
        Random r = new Random();
        int x,y;
        x= agent.getPosition().getPosX();
        y= agent.getPosition().getPosY();
        grille[y][x]=true;
        agents.add(agent);
    }
    
    public void addObserver(Observer obs){
        observers.add(obs);
    }
    
    public boolean estOccupee(int x, int y){
        return grille[y][x];
    }
    
    public void occuper(int x, int y){
        grille[y][x]=true;
    }
    
    public void liberer(int x, int y){
        grille[y][x]=false;
    }
}   
