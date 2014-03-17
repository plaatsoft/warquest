package nl.warquest.database;
// Generated 17-mrt-2014 21:30:25 by Hibernate Tools 3.2.2.GA


import java.util.Date;
import javax.persistence.Column;
import javax.persistence.Entity;
import javax.persistence.GeneratedValue;
import static javax.persistence.GenerationType.IDENTITY;
import javax.persistence.Id;
import javax.persistence.Table;
import javax.persistence.Temporal;
import javax.persistence.TemporalType;

/**
 * Bounty generated by hbm2java
 */
@Entity
@Table(name="bounty"
    ,catalog="warquest"
)
public class Bounty  implements java.io.Serializable {


     private Integer id;
     private int pid1;
     private int pid2;
     private long amount;
     private int experience;
     private Date date;

    public Bounty() {
    }

    public Bounty(int pid1, int pid2, long amount, int experience, Date date) {
       this.pid1 = pid1;
       this.pid2 = pid2;
       this.amount = amount;
       this.experience = experience;
       this.date = date;
    }
   
     @Id @GeneratedValue(strategy=IDENTITY)
    
    @Column(name="id", nullable=false)
    public Integer getId() {
        return this.id;
    }
    
    public void setId(Integer id) {
        this.id = id;
    }
    
    @Column(name="pid1", nullable=false)
    public int getPid1() {
        return this.pid1;
    }
    
    public void setPid1(int pid1) {
        this.pid1 = pid1;
    }
    
    @Column(name="pid2", nullable=false)
    public int getPid2() {
        return this.pid2;
    }
    
    public void setPid2(int pid2) {
        this.pid2 = pid2;
    }
    
    @Column(name="amount", nullable=false)
    public long getAmount() {
        return this.amount;
    }
    
    public void setAmount(long amount) {
        this.amount = amount;
    }
    
    @Column(name="experience", nullable=false)
    public int getExperience() {
        return this.experience;
    }
    
    public void setExperience(int experience) {
        this.experience = experience;
    }
    @Temporal(TemporalType.TIMESTAMP)
    @Column(name="date", nullable=false, length=19)
    public Date getDate() {
        return this.date;
    }
    
    public void setDate(Date date) {
        this.date = date;
    }




}


