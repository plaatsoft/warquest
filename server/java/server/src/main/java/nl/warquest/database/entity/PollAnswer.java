package nl.warquest.database.entity;
// Generated 18-mrt-2014 21:03:36 by Hibernate Tools 3.2.2.GA


import javax.persistence.Column;
import javax.persistence.Entity;
import javax.persistence.GeneratedValue;
import static javax.persistence.GenerationType.IDENTITY;
import javax.persistence.Id;
import javax.persistence.Table;

/**
 * PollAnswer generated by hbm2java
 */
@Entity
@Table(name="poll_answer"
    ,catalog="warquest"
)
public class PollAnswer  implements java.io.Serializable {


     private Integer answerId;
     private int pollId;
     private String answer;

    public PollAnswer() {
    }

    public PollAnswer(int pollId, String answer) {
       this.pollId = pollId;
       this.answer = answer;
    }
   
     @Id @GeneratedValue(strategy=IDENTITY)
    
    @Column(name="answer_id", nullable=false)
    public Integer getAnswerId() {
        return this.answerId;
    }
    
    public void setAnswerId(Integer answerId) {
        this.answerId = answerId;
    }
    
    @Column(name="poll_id", nullable=false)
    public int getPollId() {
        return this.pollId;
    }
    
    public void setPollId(int pollId) {
        this.pollId = pollId;
    }
    
    @Column(name="answer", nullable=false, length=128)
    public String getAnswer() {
        return this.answer;
    }
    
    public void setAnswer(String answer) {
        this.answer = answer;
    }




}


