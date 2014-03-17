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
 * PlayerLottery generated by hbm2java
 */
@Entity
@Table(name="player_lottery"
    ,catalog="warquest"
)
public class PlayerLottery  implements java.io.Serializable {


     private Integer id;
     private int pid;
     private int lotteryId;
     private Date betDate;
     private int winner;

    public PlayerLottery() {
    }

    public PlayerLottery(int pid, int lotteryId, Date betDate, int winner) {
       this.pid = pid;
       this.lotteryId = lotteryId;
       this.betDate = betDate;
       this.winner = winner;
    }
   
     @Id @GeneratedValue(strategy=IDENTITY)
    
    @Column(name="id", nullable=false)
    public Integer getId() {
        return this.id;
    }
    
    public void setId(Integer id) {
        this.id = id;
    }
    
    @Column(name="pid", nullable=false)
    public int getPid() {
        return this.pid;
    }
    
    public void setPid(int pid) {
        this.pid = pid;
    }
    
    @Column(name="lottery_id", nullable=false)
    public int getLotteryId() {
        return this.lotteryId;
    }
    
    public void setLotteryId(int lotteryId) {
        this.lotteryId = lotteryId;
    }
    @Temporal(TemporalType.TIMESTAMP)
    @Column(name="bet_date", nullable=false, length=19)
    public Date getBetDate() {
        return this.betDate;
    }
    
    public void setBetDate(Date betDate) {
        this.betDate = betDate;
    }
    
    @Column(name="winner", nullable=false)
    public int getWinner() {
        return this.winner;
    }
    
    public void setWinner(int winner) {
        this.winner = winner;
    }




}


