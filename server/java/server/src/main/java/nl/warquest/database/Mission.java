package nl.warquest.database;
// Generated 17-mrt-2014 21:30:25 by Hibernate Tools 3.2.2.GA


import javax.persistence.Column;
import javax.persistence.Entity;
import javax.persistence.Id;
import javax.persistence.Table;

/**
 * Mission generated by hbm2java
 */
@Entity
@Table(name="mission"
    ,catalog="warquest"
)
public class Mission  implements java.io.Serializable {


     private int mid;
     private long minPrice;
     private long maxPrice;
     private int experience;
     private int loot;
     private int energy;
     private int alliance;
     private int lid;
     private int mgid;

    public Mission() {
    }

    public Mission(int mid, long minPrice, long maxPrice, int experience, int loot, int energy, int alliance, int lid, int mgid) {
       this.mid = mid;
       this.minPrice = minPrice;
       this.maxPrice = maxPrice;
       this.experience = experience;
       this.loot = loot;
       this.energy = energy;
       this.alliance = alliance;
       this.lid = lid;
       this.mgid = mgid;
    }
   
     @Id 
    
    @Column(name="mid", nullable=false)
    public int getMid() {
        return this.mid;
    }
    
    public void setMid(int mid) {
        this.mid = mid;
    }
    
    @Column(name="min_price", nullable=false)
    public long getMinPrice() {
        return this.minPrice;
    }
    
    public void setMinPrice(long minPrice) {
        this.minPrice = minPrice;
    }
    
    @Column(name="max_price", nullable=false)
    public long getMaxPrice() {
        return this.maxPrice;
    }
    
    public void setMaxPrice(long maxPrice) {
        this.maxPrice = maxPrice;
    }
    
    @Column(name="experience", nullable=false)
    public int getExperience() {
        return this.experience;
    }
    
    public void setExperience(int experience) {
        this.experience = experience;
    }
    
    @Column(name="loot", nullable=false)
    public int getLoot() {
        return this.loot;
    }
    
    public void setLoot(int loot) {
        this.loot = loot;
    }
    
    @Column(name="energy", nullable=false)
    public int getEnergy() {
        return this.energy;
    }
    
    public void setEnergy(int energy) {
        this.energy = energy;
    }
    
    @Column(name="alliance", nullable=false)
    public int getAlliance() {
        return this.alliance;
    }
    
    public void setAlliance(int alliance) {
        this.alliance = alliance;
    }
    
    @Column(name="lid", nullable=false)
    public int getLid() {
        return this.lid;
    }
    
    public void setLid(int lid) {
        this.lid = lid;
    }
    
    @Column(name="mgid", nullable=false)
    public int getMgid() {
        return this.mgid;
    }
    
    public void setMgid(int mgid) {
        this.mgid = mgid;
    }




}


