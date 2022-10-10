using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.EventSystems;

public class Skills : MonoBehaviour, IPointerEnterHandler, IPointerExitHandler
{
    // Start is called before the first frame update
    private Image sprite;

    [SerializeField]
    private Text countText;

    [SerializeField]
    private int maxCount;

    private int currentCount;

    [SerializeField]
    public bool unlocked;

    [SerializeField]
    private Skills childSkill;

    public bool skillAvailable = false;
    [SerializeField]
    private GameObject tooltip;


    private void Awake()
    {
        sprite = GetComponent<Image>();
        countText.text = $"{currentCount}/{maxCount}";

        if (unlocked)
        {
            Unlock();
        }
    }

    public bool Click()
    {
        if (currentCount < maxCount && unlocked)
        {
            currentCount++;
            countText.text = $"{currentCount}/{maxCount}";

            if (currentCount == maxCount)
            {
                skillAvailable = true;
                if (childSkill != null)
                {
                    childSkill.Unlock();
                }
            }

            return true;
        }
        return false;
    }

    public void Lock()
    {
        sprite.color = Color.gray;
        countText.color = Color.gray;
    }

    public void Unlock()
    {
        sprite.color = Color.white;
        countText.color = Color.white;

        unlocked = true;
    }

    public void OnPointerEnter(PointerEventData eventData)
    {
        ShowTooltip();
    }

    public void OnPointerExit(PointerEventData eventData)
    {
        HideTooltip();
    }

    public void ShowTooltip()
    {
        tooltip.SetActive(true);
    }

    public void HideTooltip()
    {
        tooltip.SetActive(false);
    }
}
