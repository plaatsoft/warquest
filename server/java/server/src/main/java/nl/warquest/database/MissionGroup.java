package nl.warquest.database;
// Generated 17-mrt-2014 21:30:25 by Hibernate Tools 3.2.2.GA


import javax.persistence.Column;
import javax.persistence.Entity;
import javax.persistence.Id;
import javax.persistence.Table;

/**
 * MissionGroup generated by hbm2java
 */
@Entity
@Table(name="mission_group"
    ,catalog="warquest"
)
public class MissionGroup  implements java.io.Serializable {


     private int mgid;
     private int planet;

    public MissionGroup() {
    }

    public MissionGroup(int mgid, int planet) {
       this.mgid = mgid;
       this.planet = planet;
    }
   
     @Id 
    
    @Column(name="mgid", nullable=false)
    public int getMgid() {
        return this.mgid;
    }
    
    public void setMgid(int mgid) {
        this.mgid = mgid;
    }
    
    @Column(name="planet", nullable=false)
    public int getPlanet() {
        return this.planet;
    }
    
    public void setPlanet(int planet) {
        this.planet = planet;
    }




}


