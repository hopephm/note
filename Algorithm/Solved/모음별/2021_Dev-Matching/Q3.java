import java.util.*;

class Solution {
    private class Person{
        private String name;
        private int benefit;
        private Person parent;

        public Person(String name){
            this.name = name;
            this.benefit = 0;
        }

        public void setParent(Person parent){
            this.parent = parent;
        }

        public int getBenefit(){
            return this.benefit;
        }

        public void appendBenefit(int amount){
            if(!this.name.equals("-")) this.parent.appendBenefit((int)(amount*0.1));
            this.benefit += amount-(int)(amount*0.1);
        }


    }

    public int[] solution(String[] enroll, String[] referral, String[] seller, int[] amount) {
        int[] answer = new int[enroll.length];
        Map<String, Person> persons = new HashMap<String, Person>();
        
        persons.put("-", new Person("-"));
        for(int i = 0; i < enroll.length; i++){
            persons.put(enroll[i], new Person(enroll[i]));
        }

        for(int i = 0; i < referral.length; i++){
            persons.get(enroll[i]).setParent(persons.get(referral[i]));
        }
        
        for(int i = 0; i < seller.length; i++){
            persons.get(seller[i]).appendBenefit(amount[i]*100);
        }

        for(int i = 0; i < enroll.length; i++){
            answer[i] = persons.get(enroll[i]).getBenefit();
        }

        return answer;
    }
}