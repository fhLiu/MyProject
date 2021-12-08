#pragma once

struct StudyAbroad
{
    void TemplateMethod();
    virtual void LookingForSchool() = 0;
    void ApplyForEnrol();
    virtual void ApplyForPassport();
    virtual void ApplyForVisa() = 0;
    virtual void ReadyGoAbroad() = 0;
    virtual ~StudyAbroad(){}
};
