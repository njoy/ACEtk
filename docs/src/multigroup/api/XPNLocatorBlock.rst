.. currentmodule:: ACEtk.multigroup

XPNLocatorBlock
===============

The `XPNL` block holds the locators for the `XPN` blocks within the XSS array.
These locators are absolute within the full XSS array. 
There are `NSEC` secondary particles and `NSEC` +1 `XPN` blocks, which do not need to be contiguous.
The first locator is the `XPN` block for the incident particle, and the rest are the for the secondary particles in the same order as in the :class:`SecondaryParticleTypeBlock`.

There are separate functions on the :class:`XPNLocatorBlock` object to return the locator for the incident particle and for the secondary particles.
This is to allow consistency with the indices of the secondary particles in the :class:`SecondaryParticleTypeBlock` block.

Constructors
~~~~~~~~~~~~
.. autosummary::
    :toctree:  generated/

    ~XPNLocatorBlock


ACE Variables
~~~~~~~~~~~~~
.. autosummary::
    :toctree: generated/

    ~XPNLocatorBlock.NSEC
    ~XPNLocatorBlock.LXPN
    ~XPNLocatorBlock.LXPN1
    ~XPNLocatorBlock.xss

Human-Readable Variables
~~~~~~~~~~~~~~~~~~~~~~~~
.. autosummary::
    :toctree: generated/
    
    ~XPNLocatorBlock.number_secondary_particle_types
    ~XPNLocatorBlock.secondary_locator
    ~XPNLocatorBlock.incident_locator
    ~XPNLocatorBlock.is_isotropic
    ~XPNLocatorBlock.incident_isotropic
    ~XPNLocatorBlock.empty
    ~XPNLocatorBlock.length
    ~XPNLocatorBlock.name
    ~XPNLocatorBlock.xss_array



