package nl.warquest.database;
// Generated 17-mrt-2014 21:30:25 by Hibernate Tools 3.2.2.GA


import javax.persistence.AttributeOverride;
import javax.persistence.AttributeOverrides;
import javax.persistence.Column;
import javax.persistence.EmbeddedId;
import javax.persistence.Entity;
import javax.persistence.Table;

/**
 * MissionUnit generated by hbm2java
 */
@Entity
@Table(name="mission_unit"
    ,catalog="warquest"
)
public class MissionUnit  implements java.io.Serializable {


     private MissionUnitId id;
     private int amount;

    public MissionUnit() {
    }

    public MissionUnit(MissionUnitId id, int amount) {
       this.id = id;
       this.amount = amount;
    }
   
     @EmbeddedId
    
    @AttributeOverrides( {
        @AttributeOverride(name="mid", column=@Column(name="mid", nullable=false) ), 
        @AttributeOverride(name="uid", column=@Column(name="uid", nullable=false) ) } )
    public MissionUnitId getId() {
        return this.id;
    }
    
    public void setId(MissionUnitId id) {
        this.id = id;
    }
    
    @Column(name="amount", nullable=false)
    public int getAmount() {
        return this.amount;
    }
    
    public void setAmount(int amount) {
        this.amount = amount;
    }




}


