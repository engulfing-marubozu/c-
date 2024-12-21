why do we even need protacted members when can access base class data members using getter setters?
    --> We don’t typically use protected in normal classes because it’s specifically designed for inheritance scenarios. When there are no subclasses involved:

    Private and public already provide clear and complete control over data access and encapsulation.
    Protected adds no value because there’s no subclass to provide special access to.
    Using private for internal data and public for external methods results in simpler, cleaner code without the need for an intermediate access level like protected.

    --> The choice between using private members with getter/setter methods and using protected members ultimately depends on the context:

    Use private with getters/setters when you need strict encapsulation and control over how data is accessed/modified.
    Use protected when you want to give subclasses easy and direct access to inherited members, simplifying the design in inheritance-heavy scenarios.





