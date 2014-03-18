package nl.warquest.database;
// Generated 17-mrt-2014 21:30:25 by Hibernate Tools 3.2.2.GA


import javax.persistence.AttributeOverride;
import javax.persistence.AttributeOverrides;
import javax.persistence.Column;
import javax.persistence.EmbeddedId;
import javax.persistence.Entity;
import javax.persistence.Table;

/**
 * PlayerMission generated by hbm2java
 */
@Entity
@Table(name="player_mission"
    ,catalog="warquest"
)
public class PlayerMission  implements java.io.Serializable {


     private PlayerMissionId id;
     private int progress;
     private int part;
     private int part2;

    public PlayerMission() {
    }

    public PlayerMission(PlayerMissionId id, int progress, int part, int part2) {
       this.id = id;
       this.progress = progress;
       this.part = part;
       this.part2 = part2;
    }
   
     @EmbeddedId
    
    @AttributeOverrides( {
        @AttributeOverride(name="pid", column=@Column(name="pid", nullable=false) ), 
        @AttributeOverride(name="mid", column=@Column(name="mid", nullable=false) ) } )
    public PlayerMissionId getId() {
        return this.id;
    }
    
    public void setId(PlayerMissionId id) {
        this.id = id;
    }
    
    @Column(name="progress", nullable=false)
    public int getProgress() {
        return this.progress;
    }
    
    public void setProgress(int progress) {
        this.progress = progress;
    }
    
    @Column(name="part", nullable=false)
    public int getPart() {
        return this.part;
    }
    
    public void setPart(int part) {
        this.part = part;
    }
    
    @Column(name="part2", nullable=false)
    public int getPart2() {
        return this.part2;
    }
    
    public void setPart2(int part2) {
        this.part2 = part2;
    }




}

