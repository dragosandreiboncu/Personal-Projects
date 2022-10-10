using System.Collections;
using System.Collections.Generic;
using System.Drawing;
using UnityEngine;
using UnityEngine.UI;

public class SkillTree : MonoBehaviour
{
    // public PlayerStats ps;
    public int points;

    [SerializeField]
    public Skills[] skills;

    [SerializeField]
    private Skills[] unclockedDefault;

    [SerializeField]
    private Text talentPointText;
    // Start is called before the first frame update

    void Start()
    {
        ResetTalents(); 
    }

    public void TryUseSkill(Skills skill)
    {
        if (points > 0 && skill.Click())
        {
            points--;
            UpdateTalentPointText();
        }
    }

    // Update is called once per frame
    void Update()
    {
        UpdateTalentPointText();
    }

    private void ResetTalents()
    {
        UpdateTalentPointText();

        foreach (Skills skill in skills)
        {
            skill.Lock();
        }

        foreach (Skills skill in unclockedDefault)
        {
            skill.Unlock();
        }
    }

    public void UpdateTalentPointText()
    {
        talentPointText.text = points.ToString();
    }
}
