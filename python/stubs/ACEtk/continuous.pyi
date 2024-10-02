"""
Continuous energy ACE blocks and components
"""
import ACEtk
from __future__ import annotations
import typing
__all__ = ['AngleEnergyDistributionData', 'AngularDistributionBlock', 'AngularDistributionData', 'CrossSectionBlock', 'CrossSectionData', 'DelayedNeutronPrecursorBlock', 'DelayedNeutronPrecursorData', 'DiscretePhotonDistribution', 'DistributionGivenElsewhere', 'DistributionProbability', 'EnergyAngleDistributionData', 'EnergyDependentWattSpectrum', 'EnergyDistributionBlock', 'EquiprobableAngularBins', 'EquiprobableOutgoingEnergyBinData', 'EquiprobableOutgoingEnergyBins', 'EvaporationSpectrum', 'FissionMultiplicityBlock', 'FrameAndMultiplicityBlock', 'FullyIsotropicDistribution', 'GeneralEvaporationSpectrum', 'InterpolationData', 'IsotropicAngularDistribution', 'KalbachMannDistributionData', 'LevelScatteringDistribution', 'MultiDistributionData', 'MultiplicityReactionNumberBlock', 'NBodyPhaseSpaceDistribution', 'OutgoingEnergyDistributionData', 'ParameterData', 'PhotonProductionBlock', 'PhotonProductionCrossSectionBlock', 'PhotonProductionCrossSectionData', 'PolynomialFissionMultiplicity', 'PrincipalCrossSectionBlock', 'ProbabilityTable', 'ProbabilityTableBlock', 'ReactionNumberBlock', 'ReactionQValueBlock', 'SecondaryParticleAngularDistributionBlock', 'SecondaryParticleEnergyDistributionBlock', 'SecondaryParticleInformationBlock', 'SecondaryParticleLocatorBlock', 'SecondaryParticleProductionBlock', 'SecondaryParticleProductionCrossSectionBlock', 'SecondaryParticleTypeBlock', 'SimpleMaxwellianFissionSpectrum', 'TabulatedAngleEnergyDistribution', 'TabulatedAngularDistribution', 'TabulatedAngularDistributionWithProbability', 'TabulatedEnergyAngleDistribution', 'TabulatedEnergyDistribution', 'TabulatedFissionMultiplicity', 'TabulatedKalbachMannDistribution', 'TabulatedMultiplicity', 'TabulatedSecondaryParticleMultiplicity', 'TwoBodyTransferDistribution', 'UndefinedDistribution']
class AngleEnergyDistributionData:
    """
    Correlated outgoing energy-angle distribution data using tabulated distributions
    ordered as E, mu, Eprime
    
    The AngleEnergyDistributionData class contains the energy-angle distributions
    for a set of incident energy values. It is used in the DLW block as ACE LAW 67.
    """
    def LOCC(self, index: int) -> int:
        """
        Return the the distribution locator for an incident energy index
        
        This locator is the value as stored in the XSS array. It is relative to
        the beginning of the DLW block.
        
        When the index is out of range an out of range exception is thrown
        (debug mode only).
        
            self     the block
            index    the index (one-based)
        """
    @typing.overload
    def __init__(self, distributions: list[TabulatedAngleEnergyDistribution], locb: int = 1) -> None:
        """
        Initialise the block
        
        Arguments:
            self             the block
            distributions    the distributions for each incident energy
            locb             the starting xss index with respect to the DLW block
                             (default = 1, the relative locators get recalculated)
        """
    @typing.overload
    def __init__(self, boundaries: list[int], interpolants: list[int], distributions: list[TabulatedAngleEnergyDistribution], locb: int = 1) -> None:
        """
        Initialise the block
        
        Arguments:
            self             the block
            boundaries       the interpolation range boundaries
            interpolants     the interpolation types for each range
            distributions    the distributions for each incident energy
            locb             the starting xss index with respect to the DLW block
                             (default = 1, the relative locators get recalculated)
        """
    def distribution(self, index: int) -> TabulatedAngleEnergyDistribution:
        """
        Return the distribution data for an incident energy index
        
        When the index is out of range an out of range exception is thrown
        (debug mode only).
        
            self     the block
            index    the index (one-based)
        """
    def distribution_locator(self, index: int) -> int:
        """
        Return the the distribution locator for an incident energy index
        
        This locator is the value as stored in the XSS array. It is relative to
        the beginning of the DLW block.
        
        When the index is out of range an out of range exception is thrown
        (debug mode only).
        
            self     the block
            index    the index (one-based)
        """
    def incident_energy(self, index: int) -> float:
        """
        Return the incident energy for a given index
        
        When the index is out of range an out of range exception is thrown
        (debug mode only).
        
            self     the block
            index    the index (one-based)
        """
    def relative_distribution_locator(self, index: int) -> int:
        """
        Return the relative distribution locator for an incident energy index
        
        This is the locator relative to the beginning of the current angular
        distribution block in the DLW block. It is always positive.
        
        When the index is out of range an out of range exception is thrown
        (debug mode only).
        
            self     the block
            index    the index (one-based)
        """
    @typing.overload
    def xss(self, index: int) -> float:
        """
        Return a value from the xss array of the block
        
        Arguments:
            self     the data block
            index    the index (one-based)
        """
    @typing.overload
    def xss(self, index: int, length: int) -> ...:
        """
        Return a subrange of a given length from the xss array of the block
        
        Arguments:
            self      the data block
            index     the index (one-based)
            length    the length of the subrange
        """
    @property
    def INT(self) -> ...:
        """
        The interpolation type for each range
        """
    @property
    def LAW(self) -> ACEtk.EnergyDistributionType:
        """
        The distribution type
        """
    @property
    def NB(self) -> int:
        """
        The number of interpolation regions
        """
    @property
    def NBT(self) -> ...:
        """
        The interpolation boundaries
        """
    @property
    def NE(self) -> int:
        """
        The number of incident energy values
        """
    @property
    def boundaries(self) -> ...:
        """
        The interpolation boundaries
        """
    @property
    def distributions(self) -> list[TabulatedAngleEnergyDistribution]:
        """
        The distributions
        """
    @property
    def empty(self) -> bool:
        """
        Whether or not the block is empty
        """
    @property
    def incident_energies(self) -> ...:
        """
        The incident energy values
        """
    @property
    def interpolants(self) -> ...:
        """
        The interpolation type for each range
        """
    @property
    def interpolation_data(self) -> InterpolationData:
        """
        The interpolation data
        """
    @property
    def length(self) -> int:
        """
        The length of the the xss array of the block
        """
    @property
    def maximum_incident_energy(self) -> float:
        """
        The maximum incident energy for the distribution
        """
    @property
    def minimum_incident_energy(self) -> float:
        """
        The minimum incident energy for the distribution
        """
    @property
    def name(self) -> str:
        """
        The name of the block
        """
    @property
    def number_incident_energies(self) -> int:
        """
        The number of incident energy values
        """
    @property
    def number_interpolation_regions(self) -> int:
        """
        The number of interpolation regions
        """
    @property
    def type(self) -> ACEtk.EnergyDistributionType:
        """
        The distribution type
        """
    @property
    def xss_array(self) -> ...:
        """
        The xss array of the block
        """
class AngularDistributionBlock:
    """
    The AngularDistributionBlock class contains angular distribution data,
    one for each the first NXS(5) reaction numbers on the MTR block and
    elastic as well (referenced using the reaction index 0). Elastic is always
    the first reaction (hence the index 0 for this reaction) while the order
    of the other distribution data sets is the same as the order of the reaction
    numbers in the MTR block.
    """
    def LAND(self, index: int) -> int:
        """
        Return the relative angular distribution locator for a reaction index
        
        When the index is out of range an out of range exception is thrown
        (debug mode only).
        
            self     the block
            index    the index (one-based, zero for elastic)
        """
    def __init__(self, elastic: FullyIsotropicDistribution | DistributionGivenElsewhere | AngularDistributionData, distributions: list[FullyIsotropicDistribution | DistributionGivenElsewhere | AngularDistributionData]) -> None:
        """
        Initialise the block
        
        Arguments:
            self             the block
            elastic          the angular distribution data for elastic
            distributions    the angular distribution data
        """
    def angular_distribution_data(self, index: int) -> FullyIsotropicDistribution | DistributionGivenElsewhere | AngularDistributionData:
        """
        Return the angular distribution data for a reaction index
        
        When the index is out of range an out of range exception is thrown
        (debug mode only).
        
            self     the block
            index    the index (one-based, zero for elastic)
        """
    def angular_distribution_locator(self, index: int) -> int:
        """
        Return the relative angular distribution locator for a reaction index
        
        When the index is out of range an out of range exception is thrown
        (debug mode only).
        
            self     the block
            index    the index (one-based, zero for elastic)
        """
    def is_fully_isotropic(self, index: int) -> bool:
        """
        Return whether or not the distribution data is fully isotropic for
        a reaction index
        
        When the index is out of range an out of range exception is thrown
        (debug mode only).
        
            self     the block
            index    the index (one-based, zero for elastic)
        """
    def is_given(self, index: int) -> bool:
        """
        Return whether or not the distribution data is fully isotropic for
        is given in the AND block
        
        When the index is out of range an out of range exception is thrown
        (debug mode only).
        
            self     the block
            index    the index (one-based, zero for elastic)
        """
    @typing.overload
    def xss(self, index: int) -> float:
        """
        Return a value from the xss array of the block
        
        Arguments:
            self     the data block
            index    the index (one-based)
        """
    @typing.overload
    def xss(self, index: int, length: int) -> ...:
        """
        Return a subrange of a given length from the xss array of the block
        
        Arguments:
            self      the data block
            index     the index (one-based)
            length    the length of the subrange
        """
    @property
    def NR(self) -> int:
        """
        The number of reactions excluding elastic that produce the projectile
        """
    @property
    def data(self) -> list[FullyIsotropicDistribution | DistributionGivenElsewhere | AngularDistributionData]:
        """
        All angular distribution data
        """
    @property
    def empty(self) -> bool:
        """
        Whether or not the block is empty
        """
    @property
    def length(self) -> int:
        """
        The length of the the xss array of the block
        """
    @property
    def name(self) -> str:
        """
        The name of the block
        """
    @property
    def number_projectile_production_reactions(self) -> int:
        """
        The number of reactions excluding elastic that produce the projectile
        """
    @property
    def total_number_projectile_production_reactions(self) -> int:
        """
        The number of reactions excluding elastic that produce the projectile
        """
    @property
    def xss_array(self) -> ...:
        """
        The xss array of the block
        """
class AngularDistributionData:
    """
    Angular distribution data
    
    The AngularDistributionData class contains the angular distribution data
    energy distributions for a set of incident energy values. It is used in
    the AND block.
    """
    def LOCC(self, index: int) -> int:
        """
        Return the the angular distribution locator for an incident energy index
        
        This locator is the value as stored in the XSS array. It is relative to
        the beginning of the AND block. The distribution type is determined from
        the sign of the locator:
          - when the value if negative, it is a tabulated distribution
          - when the value if positive, it is an equiprobable distribution
          - when the value if zero, it is an isotropic distribution
        
        When the index is out of range an out of range exception is thrown
        (debug mode only).
        
            self     the block
            index    the index (one-based)
        """
    def __init__(self, distributions: list[IsotropicAngularDistribution | EquiprobableAngularBins | TabulatedAngularDistribution], locb: int = 1) -> None:
        """
        Initialise the block
        
        Arguments:
            self             the block
            distributions    the angular distributions for each incident energy
            locb             the starting xss index with respect to the AND block
                             (default = 1, the relative locators get recalculated)
        """
    def distribution(self, index: int) -> IsotropicAngularDistribution | EquiprobableAngularBins | TabulatedAngularDistribution:
        """
        Return the angular distribution data for an incident energy index
        
        When the index is out of range an out of range exception is thrown
        (debug mode only).
        
            self     the block
            index    the index (one-based)
        """
    def distribution_locator(self, index: int) -> int:
        """
        Return the angular distribution locator for an incident energy index
        
        This locator is the value as stored in the XSS array. It is relative to
        the beginning of the AND block. The distribution type is determined from
        the sign of the locator:
          - when the value if negative, it is a tabulated distribution
          - when the value if positive, it is an equiprobable distribution
          - when the value if zero, it is an isotropic distribution
        
        When the index is out of range an out of range exception is thrown
        (debug mode only).
        
            self     the block
            index    the index (one-based)
        """
    def distribution_type(self, index: int) -> ACEtk.AngularDistributionType:
        """
        Return the angular distribution type for an incident energy index
        
        When the index is out of range an out of range exception is thrown
        (debug mode only).
        
            self     the block
            index    the index (one-based)
        """
    def incident_energy(self, index: int) -> float:
        """
        Return the incident energy for a given index
        
        When the index is out of range an out of range exception is thrown
        (debug mode only).
        
            self     the block
            index    the index (one-based)
        """
    def relative_distribution_locator(self, index: int) -> int:
        """
        Return the relative angular distribution locator for an incident energy index
        
        This is the locator relative to the beginning of the current angular
        distribution block in the AND block. It is always positive.
        
        When the index is out of range an out of range exception is thrown
        (debug mode only).
        
            self     the block
            index    the index (one-based)
        """
    @typing.overload
    def xss(self, index: int) -> float:
        """
        Return a value from the xss array of the block
        
        Arguments:
            self     the data block
            index    the index (one-based)
        """
    @typing.overload
    def xss(self, index: int, length: int) -> ...:
        """
        Return a subrange of a given length from the xss array of the block
        
        Arguments:
            self      the data block
            index     the index (one-based)
            length    the length of the subrange
        """
    @property
    def NE(self) -> int:
        """
        The number of incident energy values
        """
    @property
    def distributions(self) -> list[IsotropicAngularDistribution | EquiprobableAngularBins | TabulatedAngularDistribution]:
        """
        The distributions
        """
    @property
    def empty(self) -> bool:
        """
        Whether or not the block is empty
        """
    @property
    def incident_energies(self) -> ...:
        """
        The incident energy values
        """
    @property
    def length(self) -> int:
        """
        The length of the the xss array of the block
        """
    @property
    def name(self) -> str:
        """
        The name of the block
        """
    @property
    def number_incident_energies(self) -> int:
        """
        The number of incident energy values
        """
    @property
    def xss_array(self) -> ...:
        """
        The xss array of the block
        """
class CrossSectionBlock:
    """
    The continuous energy LSIG and SIG block with the cross section data
    
    The CrossSectionBlock class contains NXS(4) sets of cross section values,
    one for each reaction number on the MTR block. The order of these cross
    section data sets is the same as the order of the reaction numbers in the
    MTR block.
    """
    def LSIG(self, index: int) -> int:
        """
        Return the relative cross section locator for a reaction index
        
        When the index is out of range an out of range exception is thrown
        (debug mode only).
        
            self     the block
            index    the index (one-based)
        """
    def __init__(self, xs: list[CrossSectionData]) -> None:
        """
        Initialise the block
        
        Arguments:
            self    the block
            xs      the cross section data
        """
    def cross_section_data(self, index: int) -> CrossSectionData:
        """
        Return the cross section data for a reaction index
        
        When the index is out of range an out of range exception is thrown
        (debug mode only).
        
            self     the block
            index    the index (one-based)
        """
    def cross_section_locator(self, index: int) -> int:
        """
        Return the relative cross section locator for a reaction index
        
        When the index is out of range an out of range exception is thrown
        (debug mode only).
        
            self     the block
            index    the index (one-based)
        """
    def cross_sections(self, index: int) -> ...:
        """
        Return the cross section values for a reaction index
        
        When the index is out of range an out of range exception is thrown
        (debug mode only).
        
            self     the block
            index    the index (one-based)
        """
    def energy_index(self, index: int) -> int:
        """
        Return the energy index for a reaction index
        
        When the index is out of range an out of range exception is thrown
        (debug mode only).
        
            self     the block
            index    the index (one-based)
        """
    def number_values(self, index: int) -> int:
        """
        Return the number of cross section values for a reaction index
        
        When the index is out of range an out of range exception is thrown
        (debug mode only).
        
            self     the block
            index    the index (one-based)
        """
    @typing.overload
    def xss(self, index: int) -> float:
        """
        Return a value from the xss array of the block
        
        Arguments:
            self     the data block
            index    the index (one-based)
        """
    @typing.overload
    def xss(self, index: int, length: int) -> ...:
        """
        Return a subrange of a given length from the xss array of the block
        
        Arguments:
            self      the data block
            index     the index (one-based)
            length    the length of the subrange
        """
    @property
    def NTR(self) -> int:
        """
        The number of available reactions (excluding elastic)
        """
    @property
    def data(self) -> list[CrossSectionData]:
        """
        The cross section data
        """
    @property
    def empty(self) -> bool:
        """
        Whether or not the block is empty
        """
    @property
    def length(self) -> int:
        """
        The length of the the xss array of the block
        """
    @property
    def name(self) -> str:
        """
        The name of the block
        """
    @property
    def number_reactions(self) -> int:
        """
        The number of available reactions (excluding elastic)
        """
    @property
    def xss_array(self) -> ...:
        """
        The xss array of the block
        """
class CrossSectionData:
    """
    Convenience interface for cross section data from the SIG block
    """
    def __init__(self, index: int, values: list[float]) -> None:
        """
        Initialise the block
        
        Arguments:
            self      the block
            index     the energy index
            values    the cross section values
        """
    @typing.overload
    def xss(self, index: int) -> float:
        """
        Return a value from the xss array of the block
        
        Arguments:
            self     the data block
            index    the index (one-based)
        """
    @typing.overload
    def xss(self, index: int, length: int) -> ...:
        """
        Return a subrange of a given length from the xss array of the block
        
        Arguments:
            self      the data block
            index     the index (one-based)
            length    the length of the subrange
        """
    @property
    def cross_sections(self) -> ...:
        """
        The cross section values
        """
    @property
    def empty(self) -> bool:
        """
        Whether or not the block is empty
        """
    @property
    def energy_index(self) -> int:
        """
        The energy index
        """
    @property
    def length(self) -> int:
        """
        The length of the the xss array of the block
        """
    @property
    def name(self) -> str:
        """
        The name of the block
        """
    @property
    def number_values(self) -> int:
        """
        The number of cross section values
        """
    @property
    def xss_array(self) -> ...:
        """
        The xss array of the block
        """
class DelayedNeutronPrecursorBlock:
    """
    The continuous energy BDD block with the delayed neutron precursor data
    
    The number of precursor groups is stored in NXS(8).
    """
    def __init__(self, groups: list[DelayedNeutronPrecursorData]) -> None:
        """
        Initialise the block
        
        Arguments:
            self      the block
            groups    the cross section data
        """
    def precursor_group_data(self, index: int) -> DelayedNeutronPrecursorData:
        """
        Return the precursor data for a group index
        
        When the index is out of range an out of range exception is thrown
        (debug mode only).
        
            self     the block
            index    the index (one-based)
        """
    @typing.overload
    def xss(self, index: int) -> float:
        """
        Return a value from the xss array of the block
        
        Arguments:
            self     the data block
            index    the index (one-based)
        """
    @typing.overload
    def xss(self, index: int, length: int) -> ...:
        """
        Return a subrange of a given length from the xss array of the block
        
        Arguments:
            self      the data block
            index     the index (one-based)
            length    the length of the subrange
        """
    @property
    def NPCR(self) -> int:
        """
        The number of delayed neutron precursor groups
        """
    @property
    def data(self) -> list[DelayedNeutronPrecursorData]:
        """
        The delayed neutron precursor data
        """
    @property
    def empty(self) -> bool:
        """
        Whether or not the block is empty
        """
    @property
    def length(self) -> int:
        """
        The length of the the xss array of the block
        """
    @property
    def name(self) -> str:
        """
        The name of the block
        """
    @property
    def number_delayed_precursors(self) -> int:
        """
        The number of delayed neutron precursor groups
        """
    @property
    def xss_array(self) -> ...:
        """
        The xss array of the block
        """
class DelayedNeutronPrecursorData:
    """
    Delayed neutron precursor group data
    
    The DelayedNeutronPrecursorData class contains the precursor group's decay
    constant and the associated probability as a function of incident energy.
    """
    @typing.overload
    def __init__(self, number: int, constant: float, energies: list[float], probabilities: list[float]) -> None:
        """
        Initialise the block assuming linear interpolation
        
        Arguments:
            self             the block
            number           the precursor group number
            constant         the precursor group's decay constant
            energies         the energy values
            probabilities    the probability values
        """
    @typing.overload
    def __init__(self, number: int, constant: float, boundaries: list[int], interpolants: list[int], energies: list[float], probabilities: list[float]) -> None:
        """
        Initialise the block
        
        Arguments:
            self             the block
            number           the precursor group number
            constant         the precursor group's decay constant
            boundaries       the interpolation range boundaries
            interpolants     the interpolation types for each range
            energies         the energy values
            probabilities    the probability values
        """
    @typing.overload
    def xss(self, index: int) -> float:
        """
        Return a value from the xss array of the block
        
        Arguments:
            self     the data block
            index    the index (one-based)
        """
    @typing.overload
    def xss(self, index: int, length: int) -> ...:
        """
        Return a subrange of a given length from the xss array of the block
        
        Arguments:
            self      the data block
            index     the index (one-based)
            length    the length of the subrange
        """
    @property
    def DEC(self) -> float:
        """
        The precursor group's decay constant
        """
    @property
    def E(self) -> ...:
        """
        The energy values
        """
    @property
    def INT(self) -> ...:
        """
        The interpolants
        """
    @property
    def NB(self) -> int:
        """
        The number of interpolation regions
        """
    @property
    def NBT(self) -> ...:
        """
        The interpolation boundaries
        """
    @property
    def NE(self) -> int:
        """
        The number of values
        """
    @property
    def P(self) -> ...:
        """
        The probabilities
        """
    @property
    def boundaries(self) -> ...:
        """
        The interpolation boundaries
        """
    @property
    def decay_constant(self) -> float:
        """
        The precursor group's decay constant
        """
    @property
    def empty(self) -> bool:
        """
        Whether or not the block is empty
        """
    @property
    def energies(self) -> ...:
        """
        The energy values
        """
    @property
    def interpolants(self) -> ...:
        """
        The interpolants
        """
    @property
    def interpolation_data(self) -> InterpolationData:
        """
        The interpolation data
        """
    @property
    def length(self) -> int:
        """
        The length of the the xss array of the block
        """
    @property
    def name(self) -> str:
        """
        The name of the block
        """
    @property
    def number(self) -> int:
        """
        The precursor group number
        """
    @property
    def number_interpolation_regions(self) -> int:
        """
        The number of interpolation regions
        """
    @property
    def number_values(self) -> int:
        """
        The number of values
        """
    @property
    def probabilities(self) -> ...:
        """
        The probabilities
        """
    @property
    def xss_array(self) -> ...:
        """
        The xss array of the block
        """
class DiscretePhotonDistribution:
    """
    The DiscretePhotonDistribution class contains the photon energy if the
    photon is a primary photon or the binding energy when the photon is not a
    primary photon. It is used in the DLW block as ACE LAW 2.
    """
    def __init__(self, emin: float, emax: float, lp: int, energy: float) -> None:
        """
        Initialise the block
        
        Arguments:
            self      the block
            emin      the minimum energy for the distribution
            emax      the maximum energy for the distribution
            lp        the primary photon flag (0, 1 or 2)
            energy    the photon or binding energy
        """
    @typing.overload
    def xss(self, index: int) -> float:
        """
        Return a value from the xss array of the block
        
        Arguments:
            self     the data block
            index    the index (one-based)
        """
    @typing.overload
    def xss(self, index: int, length: int) -> ...:
        """
        Return a subrange of a given length from the xss array of the block
        
        Arguments:
            self      the data block
            index     the index (one-based)
            length    the length of the subrange
        """
    @property
    def EG(self) -> float:
        """
        The photon or binding energy
        """
    @property
    def LAW(self) -> ACEtk.EnergyDistributionType:
        """
        The distribution type
        """
    @property
    def LP(self) -> int:
        """
        The primary flag value (0, 1 or 2)
        """
    @property
    def empty(self) -> bool:
        """
        Whether or not the block is empty
        """
    @property
    def is_primary_photon(self) -> bool:
        """
        Indicates whether or not the photon is a primary photon
        """
    @property
    def length(self) -> int:
        """
        The length of the the xss array of the block
        """
    @property
    def maximum_incident_energy(self) -> float:
        """
        The maximum incident energy for the distribution
        """
    @property
    def minimum_incident_energy(self) -> float:
        """
        The minimum incident energy for the distribution
        """
    @property
    def name(self) -> str:
        """
        The name of the block
        """
    @property
    def photon_or_binding_energy(self) -> float:
        """
        The photon or binding energy
        """
    @property
    def primary_photon_flag(self) -> int:
        """
        The primary flag value (0, 1 or 2)
        """
    @property
    def type(self) -> ACEtk.EnergyDistributionType:
        """
        The distribution type
        """
    @property
    def xss_array(self) -> ...:
        """
        The xss array of the block
        """
class DistributionGivenElsewhere:
    """
    The angular distribution is given in a different block
    
    The DistributionGivenElsewhere class contains contains no data. It is a
    convenience interface object used in the AND block.
    """
    def __init__(self) -> None:
        """
        Initialise the block
        
        Arguments:
            self    the block
        """
class DistributionProbability:
    """
    The probability for a distribution to occur
    """
    @typing.overload
    def __init__(self, energies: list[float], probabilities: list[float]) -> None:
        """
        Initialise the block assuming linear interpolation
        
        Arguments:
            self             the block
            energies         the energy values
            probabilities    the probability values
        """
    @typing.overload
    def __init__(self, boundaries: list[int], interpolants: list[int], energies: list[float], probabilities: list[float]) -> None:
        """
        Initialise the block
        
        Arguments:
            self            the block
            boundaries      the interpolation range boundaries
            interpolants    the interpolation types for each range
            energies        the energy values
            probabilities   the probability values
        """
    @typing.overload
    def xss(self, index: int) -> float:
        """
        Return a value from the xss array of the block
        
        Arguments:
            self     the data block
            index    the index (one-based)
        """
    @typing.overload
    def xss(self, index: int, length: int) -> ...:
        """
        Return a subrange of a given length from the xss array of the block
        
        Arguments:
            self      the data block
            index     the index (one-based)
            length    the length of the subrange
        """
    @property
    def INT(self) -> ...:
        """
        The interpolation type for each range
        """
    @property
    def NB(self) -> int:
        """
        The number of interpolation regions
        """
    @property
    def NBT(self) -> ...:
        """
        The interpolation boundaries
        """
    @property
    def NE(self) -> int:
        """
        The number of energy values
        """
    @property
    def boundaries(self) -> ...:
        """
        The interpolation boundaries
        """
    @property
    def empty(self) -> bool:
        """
        Whether or not the block is empty
        """
    @property
    def energies(self) -> ...:
        """
        The energy values
        """
    @property
    def interpolants(self) -> ...:
        """
        The interpolation type for each range
        """
    @property
    def interpolation_data(self) -> InterpolationData:
        """
        The interpolation data
        """
    @property
    def length(self) -> int:
        """
        The length of the the xss array of the block
        """
    @property
    def name(self) -> str:
        """
        The name of the block
        """
    @property
    def number_energy_points(self) -> int:
        """
        The number of energy values
        """
    @property
    def number_interpolation_regions(self) -> int:
        """
        The number of interpolation regions
        """
    @property
    def probabilities(self) -> ...:
        """
        The probability values
        """
    @property
    def xss_array(self) -> ...:
        """
        The xss array of the block
        """
class EnergyAngleDistributionData:
    """
    Correlated outgoing energy-angle distribution data using tabulated distributions
    ordered as E, Eprime, mu
    
    The EnergyAngleDistributionData class contains the energy-angle distributions
    for a set of incident energy values. It is used in the DLW block as ACE LAW 61.
    """
    def LOCC(self, index: int) -> int:
        """
        Return the the distribution locator for an incident energy index
        
        This locator is the value as stored in the XSS array. It is relative to
        the beginning of the DLW block.
        
        When the index is out of range an out of range exception is thrown
        (debug mode only).
        
            self     the block
            index    the index (one-based)
        """
    @typing.overload
    def __init__(self, distributions: list[TabulatedEnergyAngleDistribution], locb: int = 1) -> None:
        """
        Initialise the block
        
        Arguments:
            self             the block
            distributions    the distributions for each incident energy
            locb             the starting xss index with respect to the DLW block
                             (default = 1, the relative locators get recalculated)
        """
    @typing.overload
    def __init__(self, boundaries: list[int], interpolants: list[int], distributions: list[TabulatedEnergyAngleDistribution], locb: int = 1) -> None:
        """
        Initialise the block
        
        Arguments:
            self             the block
            boundaries       the interpolation range boundaries
            interpolants     the interpolation types for each range
            distributions    the distributions for each incident energy
            locb             the starting xss index with respect to the DLW block
                             (default = 1, the relative locators get recalculated)
        """
    def distribution(self, index: int) -> TabulatedEnergyAngleDistribution:
        """
        Return the distribution data for an incident energy index
        
        When the index is out of range an out of range exception is thrown
        (debug mode only).
        
            self     the block
            index    the index (one-based)
        """
    def distribution_locator(self, index: int) -> int:
        """
        Return the the distribution locator for an incident energy index
        
        This locator is the value as stored in the XSS array. It is relative to
        the beginning of the DLW block.
        
        When the index is out of range an out of range exception is thrown
        (debug mode only).
        
            self     the block
            index    the index (one-based)
        """
    def incident_energy(self, index: int) -> float:
        """
        Return the incident energy for a given index
        
        When the index is out of range an out of range exception is thrown
        (debug mode only).
        
            self     the block
            index    the index (one-based)
        """
    def relative_distribution_locator(self, index: int) -> int:
        """
        Return the relative distribution locator for an incident energy index
        
        This is the locator relative to the beginning of the current angular
        distribution block in the DLW block. It is always positive.
        
        When the index is out of range an out of range exception is thrown
        (debug mode only).
        
            self     the block
            index    the index (one-based)
        """
    @typing.overload
    def xss(self, index: int) -> float:
        """
        Return a value from the xss array of the block
        
        Arguments:
            self     the data block
            index    the index (one-based)
        """
    @typing.overload
    def xss(self, index: int, length: int) -> ...:
        """
        Return a subrange of a given length from the xss array of the block
        
        Arguments:
            self      the data block
            index     the index (one-based)
            length    the length of the subrange
        """
    @property
    def INT(self) -> ...:
        """
        The interpolation type for each range
        """
    @property
    def LAW(self) -> ACEtk.EnergyDistributionType:
        """
        The distribution type
        """
    @property
    def NB(self) -> int:
        """
        The number of interpolation regions
        """
    @property
    def NBT(self) -> ...:
        """
        The interpolation boundaries
        """
    @property
    def NE(self) -> int:
        """
        The number of incident energy values
        """
    @property
    def boundaries(self) -> ...:
        """
        The interpolation boundaries
        """
    @property
    def distributions(self) -> list[TabulatedEnergyAngleDistribution]:
        """
        The distributions
        """
    @property
    def empty(self) -> bool:
        """
        Whether or not the block is empty
        """
    @property
    def incident_energies(self) -> ...:
        """
        The incident energy values
        """
    @property
    def interpolants(self) -> ...:
        """
        The interpolation type for each range
        """
    @property
    def interpolation_data(self) -> InterpolationData:
        """
        The interpolation data
        """
    @property
    def length(self) -> int:
        """
        The length of the the xss array of the block
        """
    @property
    def maximum_incident_energy(self) -> float:
        """
        The maximum incident energy for the distribution
        """
    @property
    def minimum_incident_energy(self) -> float:
        """
        The minimum incident energy for the distribution
        """
    @property
    def name(self) -> str:
        """
        The name of the block
        """
    @property
    def number_incident_energies(self) -> int:
        """
        The number of incident energy values
        """
    @property
    def number_interpolation_regions(self) -> int:
        """
        The number of interpolation regions
        """
    @property
    def type(self) -> ACEtk.EnergyDistributionType:
        """
        The distribution type
        """
    @property
    def xss_array(self) -> ...:
        """
        The xss array of the block
        """
class EnergyDependentWattSpectrum:
    """
    An energy dependent Watt spectrum
    
    The EnergyDependentWattSpectrum class contains the tabulated values for the
    energy dependent a and b parameters as well as the restriction energy U used
    to describe the Watt spectrum. It is used in the DLW block as ACE LAW 11.
    """
    def __init__(self, a: ParameterData, b: ParameterData, energy: float) -> None:
        """
        Initialise the block
        
        Arguments:
            self      the block
            a         the data for parameter a
            b         the data for parameter b
            energy    the restriction energy
        """
    @typing.overload
    def xss(self, index: int) -> float:
        """
        Return a value from the xss array of the block
        
        Arguments:
            self     the data block
            index    the index (one-based)
        """
    @typing.overload
    def xss(self, index: int, length: int) -> ...:
        """
        Return a subrange of a given length from the xss array of the block
        
        Arguments:
            self      the data block
            index     the index (one-based)
            length    the length of the subrange
        """
    @property
    def LAW(self) -> ACEtk.EnergyDistributionType:
        """
        The distribution type
        """
    @property
    def U(self) -> float:
        """
        The restriction energy
        """
    @property
    def a(self) -> ParameterData:
        """
        The data for parameter a
        """
    @property
    def b(self) -> ParameterData:
        """
        The data for parameter b
        """
    @property
    def empty(self) -> bool:
        """
        Whether or not the block is empty
        """
    @property
    def length(self) -> int:
        """
        The length of the the xss array of the block
        """
    @property
    def maximum_incident_energy(self) -> float:
        """
        The maximum incident energy for the distribution
        """
    @property
    def minimum_incident_energy(self) -> float:
        """
        The minimum incident energy for the distribution
        """
    @property
    def name(self) -> str:
        """
        The name of the block
        """
    @property
    def restriction_energy(self) -> float:
        """
        The restriction energy
        """
    @property
    def type(self) -> ACEtk.EnergyDistributionType:
        """
        The distribution type
        """
    @property
    def xss_array(self) -> ...:
        """
        The xss array of the block
        """
class EnergyDistributionBlock:
    """
    The continuous energy LDLW and DLW block with the energy distribution data
    
    The EnergyDistributionBlock class contains energy distribution data,
    one for each the first NXS(5) reaction numbers on the MTR block. The order
    of the distribution data sets is the same as the order of the reaction
    numbers in the MTR block.
    """
    def LDLW(self, index: int) -> int:
        """
        Return the relative energy distribution locator for a reaction index
        
        When the index is out of range an out of range exception is thrown
        (debug mode only).
        
            self     the block
            index    the index (one-based)
        """
    def __init__(self, distributions: list[EquiprobableOutgoingEnergyBinData | DiscretePhotonDistribution | LevelScatteringDistribution | OutgoingEnergyDistributionData | GeneralEvaporationSpectrum | SimpleMaxwellianFissionSpectrum | EvaporationSpectrum | EnergyDependentWattSpectrum | KalbachMannDistributionData | NBodyPhaseSpaceDistribution | TwoBodyTransferDistribution | EnergyAngleDistributionData | AngleEnergyDistributionData | MultiDistributionData | UndefinedDistribution], multiplicities: list[int | TabulatedMultiplicity], frames: list[ACEtk.ReferenceFrame]) -> None:
        """
        Initialise the block
        
        Arguments:
            self              the block
            distributions     the energy distribution data
            multiplicities    the multiplicity data
            frames            the reference frames
        """
    def energy_distribution_data(self, index: int) -> EquiprobableOutgoingEnergyBinData | DiscretePhotonDistribution | LevelScatteringDistribution | OutgoingEnergyDistributionData | GeneralEvaporationSpectrum | SimpleMaxwellianFissionSpectrum | EvaporationSpectrum | EnergyDependentWattSpectrum | KalbachMannDistributionData | NBodyPhaseSpaceDistribution | TwoBodyTransferDistribution | EnergyAngleDistributionData | AngleEnergyDistributionData | MultiDistributionData | UndefinedDistribution:
        """
        Return the energy distribution data for a reaction index
        
        When the index is out of range an out of range exception is thrown
        (debug mode only).
        
            self     the block
            index    the index (one-based)
        """
    def energy_distribution_locator(self, index: int) -> int:
        """
        Return the relative energy distribution locator for a reaction index
        
        When the index is out of range an out of range exception is thrown
        (debug mode only).
        
            self     the block
            index    the index (one-based)
        """
    def multiplicity_data(self, index: int) -> int | TabulatedMultiplicity:
        """
        Return the multiplicity data for a reaction index
        
        When the index is out of range an out of range exception is thrown
        (debug mode only).
        
            self     the block
            index    the index (one-based)
        """
    def reference_frame(self, index: int) -> ACEtk.ReferenceFrame:
        """
        Return the reference frame for a reaction index
        
        When the index is out of range an out of range exception is thrown
        (debug mode only).
        
            self     the block
            index    the index (one-based)
        """
    @typing.overload
    def xss(self, index: int) -> float:
        """
        Return a value from the xss array of the block
        
        Arguments:
            self     the data block
            index    the index (one-based)
        """
    @typing.overload
    def xss(self, index: int, length: int) -> ...:
        """
        Return a subrange of a given length from the xss array of the block
        
        Arguments:
            self      the data block
            index     the index (one-based)
            length    the length of the subrange
        """
    @property
    def NR(self) -> int:
        """
        The number of reactions excluding elastic that produce the projectile
        """
    @property
    def data(self) -> list[EquiprobableOutgoingEnergyBinData | DiscretePhotonDistribution | LevelScatteringDistribution | OutgoingEnergyDistributionData | GeneralEvaporationSpectrum | SimpleMaxwellianFissionSpectrum | EvaporationSpectrum | EnergyDependentWattSpectrum | KalbachMannDistributionData | NBodyPhaseSpaceDistribution | TwoBodyTransferDistribution | EnergyAngleDistributionData | AngleEnergyDistributionData | MultiDistributionData | UndefinedDistribution]:
        """
        The energy distribution data
        """
    @property
    def empty(self) -> bool:
        """
        Whether or not the block is empty
        """
    @property
    def length(self) -> int:
        """
        The length of the the xss array of the block
        """
    @property
    def multiplicities(self) -> list[int | TabulatedMultiplicity]:
        """
        The multiplicity data
        """
    @property
    def name(self) -> str:
        """
        The name of the block
        """
    @property
    def number_reactions(self) -> int:
        """
        The number of reactions excluding elastic that produce the projectile
        """
    @property
    def reference_frames(self) -> list[ACEtk.ReferenceFrame]:
        """
        The reference frames
        """
    @property
    def xss_array(self) -> ...:
        """
        The xss array of the block
        """
class EquiprobableAngularBins:
    """
    Equiprobable angular bin data for a single incident energy value
    
    The EquiprobableAngularBins class contains the cosine values that make up
    the equiprobable bins (there are 33 values for defining 32 bins) for the
    associated incident energy. It is used in the AND block. This 
    format is only used in old ACE data.
    """
    def __init__(self, energy: float, cosines: list[float]) -> None:
        """
        Initialise the block
        
        Arguments:
            self        the block
            energy      the associated energy value
            cosines     the cosine values (33 values)
        """
    @typing.overload
    def xss(self, index: int) -> float:
        """
        Return a value from the xss array of the block
        
        Arguments:
            self     the data block
            index    the index (one-based)
        """
    @typing.overload
    def xss(self, index: int, length: int) -> ...:
        """
        Return a subrange of a given length from the xss array of the block
        
        Arguments:
            self      the data block
            index     the index (one-based)
            length    the length of the subrange
        """
    @property
    def cosines(self) -> ...:
        """
        The cosine values
        """
    @property
    def empty(self) -> bool:
        """
        Whether or not the block is empty
        """
    @property
    def energy(self) -> float:
        """
        The associated energy value
        """
    @property
    def length(self) -> int:
        """
        The length of the the xss array of the block
        """
    @property
    def name(self) -> str:
        """
        The name of the block
        """
    @property
    def number_bins(self) -> int:
        """
        The number of equiprobable angular bins
        """
    @property
    def xss_array(self) -> ...:
        """
        The xss array of the block
        """
class EquiprobableOutgoingEnergyBinData:
    """
    Equiprobable outgoing energy bin data
    
    The EquiprobableOutgoingEnergyBinData class contains the equiprobable bins
    for a set of incident energy values. It is used in the AND block. This
    format is only used in old ACE data.
    """
    def __init__(self, distributions: list[EquiprobableOutgoingEnergyBins]) -> None:
        """
        Initialise the block
        
        Arguments:
            self             the block
            distributions    the distributions for each incident energy
        """
    def distribution(self, index: int) -> EquiprobableOutgoingEnergyBins:
        """
        Return the outgoing energy bin values for an incident energy index
        
        When the index is out of range an out of range exception is thrown
        (debug mode only).
        
            self     the block
            index    the index (one-based)
        """
    def incident_energy(self, index: int) -> float:
        """
        Return the incident energy for a given index
        
        When the index is out of range an out of range exception is thrown
        (debug mode only).
        
            self     the block
            index    the index (one-based)
        """
    @typing.overload
    def xss(self, index: int) -> float:
        """
        Return a value from the xss array of the block
        
        Arguments:
            self     the data block
            index    the index (one-based)
        """
    @typing.overload
    def xss(self, index: int, length: int) -> ...:
        """
        Return a subrange of a given length from the xss array of the block
        
        Arguments:
            self      the data block
            index     the index (one-based)
            length    the length of the subrange
        """
    @property
    def INT(self) -> ...:
        """
        The interpolation type for each range
        """
    @property
    def LAW(self) -> ACEtk.EnergyDistributionType:
        """
        The distribution type
        """
    @property
    def NB(self) -> int:
        """
        The number of interpolation regions
        """
    @property
    def NBT(self) -> ...:
        """
        The interpolation boundaries
        """
    @property
    def NE(self) -> int:
        """
        The number of incident energy values
        """
    @property
    def NET(self) -> int:
        """
        The number of outgoing energy values for each incident energy
        """
    @property
    def boundaries(self) -> ...:
        """
        The interpolation boundaries
        """
    @property
    def distributions(self) -> list[EquiprobableOutgoingEnergyBins]:
        """
        Return the distributions
        """
    @property
    def empty(self) -> bool:
        """
        Whether or not the block is empty
        """
    @property
    def incident_energies(self) -> ...:
        """
        The incident energy values
        """
    @property
    def interpolants(self) -> ...:
        """
        The interpolation type for each range
        """
    @property
    def interpolation_data(self) -> InterpolationData:
        """
        The interpolation data
        """
    @property
    def length(self) -> int:
        """
        The length of the the xss array of the block
        """
    @property
    def maximum_incident_energy(self) -> float:
        """
        The maximum incident energy for the distribution
        """
    @property
    def minimum_incident_energy(self) -> float:
        """
        The minimum incident energy for the distribution
        """
    @property
    def name(self) -> str:
        """
        The name of the block
        """
    @property
    def number_bins(self) -> int:
        """
        The number of equiprobable outgoing energy bins
        """
    @property
    def number_incident_energies(self) -> int:
        """
        The number of incident energy values
        """
    @property
    def number_interpolation_regions(self) -> int:
        """
        The number of interpolation regions
        """
    @property
    def type(self) -> ACEtk.EnergyDistributionType:
        """
        The distribution type
        """
    @property
    def xss_array(self) -> ...:
        """
        The xss array of the block
        """
class EquiprobableOutgoingEnergyBins:
    """
    Equiprobable outgoing energy bin data for a single incident energy
    
    The EquiprobableOutgoingEnergyBins class contains the outgoing energy values
    that make up the equiprobable bins and the associated incident energy. It is
    used in the EquiprobableOutgoingEnergyBinData (ACE LAW 1 for a given incident
    energy) in the DLW block. This format is only used in old ACE data.
    """
    def __init__(self, incident: float, energies: list[float]) -> None:
        """
        Initialise the block
        
        Arguments:
            self        the block
            incident    the incident energy value
            energies    the outgoing energy values
        """
    @typing.overload
    def xss(self, index: int) -> float:
        """
        Return a value from the xss array of the block
        
        Arguments:
            self     the data block
            index    the index (one-based)
        """
    @typing.overload
    def xss(self, index: int, length: int) -> ...:
        """
        Return a subrange of a given length from the xss array of the block
        
        Arguments:
            self      the data block
            index     the index (one-based)
            length    the length of the subrange
        """
    @property
    def empty(self) -> bool:
        """
        Whether or not the block is empty
        """
    @property
    def energies(self) -> ...:
        """
        The outgoing energy values
        """
    @property
    def incident_energy(self) -> float:
        """
        The incident energy
        """
    @property
    def length(self) -> int:
        """
        The length of the the xss array of the block
        """
    @property
    def name(self) -> str:
        """
        The name of the block
        """
    @property
    def number_bins(self) -> int:
        """
        The number of equiprobable angular bins
        """
    @property
    def xss_array(self) -> ...:
        """
        The xss array of the block
        """
class EvaporationSpectrum:
    """
    An evaporation spectrum
    
    The EvaporationSpectrum class contains the tabulated energy and
    temperature values as well as the restriction energy U used to describe the
    evaporation spectrum. It is used in the DLW block as ACE LAW 9.
    """
    def __init__(self, boundaries: list[int], interpolants: list[int], energies: list[float], temperatures: list[float], energy: float) -> None:
        """
        Initialise the block
        
        Arguments:
            self            the block
            boundaries      the interpolation range boundaries
            interpolants    the interpolation types for each range
            energies        the energy values
            temperatures    the temperature values
            energy          the restriction energy
        """
    @typing.overload
    def xss(self, index: int) -> float:
        """
        Return a value from the xss array of the block
        
        Arguments:
            self     the data block
            index    the index (one-based)
        """
    @typing.overload
    def xss(self, index: int, length: int) -> ...:
        """
        Return a subrange of a given length from the xss array of the block
        
        Arguments:
            self      the data block
            index     the index (one-based)
            length    the length of the subrange
        """
    @property
    def INT(self) -> ...:
        """
        The interpolation type for each range
        """
    @property
    def LAW(self) -> ACEtk.EnergyDistributionType:
        """
        The distribution type
        """
    @property
    def NB(self) -> int:
        """
        The number of interpolation regions
        """
    @property
    def NBT(self) -> ...:
        """
        The interpolation boundaries
        """
    @property
    def NE(self) -> int:
        """
        The number of incident energy values
        """
    @property
    def U(self) -> float:
        """
        The restriction energy
        """
    @property
    def boundaries(self) -> ...:
        """
        The interpolation boundaries
        """
    @property
    def empty(self) -> bool:
        """
        Whether or not the block is empty
        """
    @property
    def energies(self) -> ...:
        """
        The incident energy values
        """
    @property
    def interpolants(self) -> ...:
        """
        The interpolation type for each range
        """
    @property
    def interpolation_data(self) -> InterpolationData:
        """
        The interpolation data
        """
    @property
    def length(self) -> int:
        """
        The length of the the xss array of the block
        """
    @property
    def maximum_incident_energy(self) -> float:
        """
        The maximum incident energy for the distribution
        """
    @property
    def minimum_incident_energy(self) -> float:
        """
        The minimum incident energy for the distribution
        """
    @property
    def name(self) -> str:
        """
        The name of the block
        """
    @property
    def number_energy_points(self) -> int:
        """
        The number of incident energy values
        """
    @property
    def number_interpolation_regions(self) -> int:
        """
        The number of interpolation regions
        """
    @property
    def restriction_energy(self) -> float:
        """
        The restriction energy
        """
    @property
    def temperatures(self) -> ...:
        """
        The temperature values
        """
    @property
    def type(self) -> ACEtk.EnergyDistributionType:
        """
        The distribution type
        """
    @property
    def xss_array(self) -> ...:
        """
        The xss array of the block
        """
class FissionMultiplicityBlock:
    """
    The continuous energy NU block with the fission multiplicity data.
    """
    @typing.overload
    def __init__(self, prompt: PolynomialFissionMultiplicity | TabulatedFissionMultiplicity) -> None:
        """
        Initialise the block
        
        Arguments:
            self      the block
            prompt    the prompt fission multiplicity data
        """
    @typing.overload
    def __init__(self, prompt: PolynomialFissionMultiplicity | TabulatedFissionMultiplicity, total: PolynomialFissionMultiplicity | TabulatedFissionMultiplicity) -> None:
        """
        Initialise the block
        
        Arguments:
            self      the block
            prompt    the prompt fission multiplicity data
            total     the total fission multiplicity data
        """
    @typing.overload
    def xss(self, index: int) -> float:
        """
        Return a value from the xss array of the block
        
        Arguments:
            self     the data block
            index    the index (one-based)
        """
    @typing.overload
    def xss(self, index: int, length: int) -> ...:
        """
        Return a subrange of a given length from the xss array of the block
        
        Arguments:
            self      the data block
            index     the index (one-based)
            length    the length of the subrange
        """
    @property
    def empty(self) -> bool:
        """
        Whether or not the block is empty
        """
    @property
    def has_prompt_and_total_fission_multiplicity(self) -> bool:
        """
        Flag to see whether or not prompt and total fission multiplicity are present
        """
    @property
    def length(self) -> int:
        """
        The length of the the xss array of the block
        """
    @property
    def multiplicity(self) -> PolynomialFissionMultiplicity | TabulatedFissionMultiplicity:
        """
        The prompt fission multiplicity
        This returns the prompt fission multiplicity when both prompt and total
        are given or just the available multiplicity data if only one of these is
        given (the ACE format does not indicate which is present).
        """
    @property
    def name(self) -> str:
        """
        The name of the block
        """
    @property
    def total_fission_multiplicity(self) -> PolynomialFissionMultiplicity | TabulatedFissionMultiplicity | None:
        """
        The total fission multiplicity
        This returns the total fission multiplicity when both prompt and total
        are given or just the available multiplicity data if only one of these is
        given (the ACE format does not indicate which is present).
        """
    @property
    def xss_array(self) -> ...:
        """
        The xss array of the block
        """
class FrameAndMultiplicityBlock:
    """
    The continuous energy TYR block with the outgoing projectile multiplicities
    and reference frames
    
    The FrameAndMultiplicityBlock class contains the reference frame and
    outgoing projectile multiplicity. The order of this data is the same as
    the order of the reaction numbers in the MTR block.
    
    The number of available reactions (excluding elastic) is stored in NXS(4).
    """
    @typing.overload
    def __init__(self, frames: list[ACEtk.ReferenceFrame], multiplicities: list[int]) -> None:
        """
        Initialise the TYR block
        
        Arguments:
            self              the block
            frames            the reference frames
            multiplicities    the multiplicities
        """
    @typing.overload
    def __init__(self, frames: list[ACEtk.ReferenceFrame]) -> None:
        """
        Initialise the TYRH block
        
        Arguments:
            self              the block
            frames            the reference frames
        """
    def multiplicity(self, index: int) -> int:
        """
        The multiplicity for a reaction index
        
        Arguments:
            self     the block
            index    the index (one-based)
        """
    def reference_frame(self, index: int) -> ACEtk.ReferenceFrame:
        """
        The reference frame for a reaction index
        
        Arguments:
            self     the block
            index    the index (one-based)
        """
    @typing.overload
    def xss(self, index: int) -> float:
        """
        Return a value from the xss array of the block
        
        Arguments:
            self     the data block
            index    the index (one-based)
        """
    @typing.overload
    def xss(self, index: int, length: int) -> ...:
        """
        Return a subrange of a given length from the xss array of the block
        
        Arguments:
            self      the data block
            index     the index (one-based)
            length    the length of the subrange
        """
    @property
    def NTR(self) -> int:
        """
        The number of available reactions (excluding elastic)
        """
    @property
    def empty(self) -> bool:
        """
        Whether or not the block is empty
        """
    @property
    def length(self) -> int:
        """
        The length of the the xss array of the block
        """
    @property
    def multiplicities(self) -> list[int]:
        """
        The reference frames
        """
    @property
    def name(self) -> str:
        """
        The name of the block
        """
    @property
    def number_reactions(self) -> int:
        """
        The number of available reactions (excluding elastic)
        """
    @property
    def reference_frames(self) -> list[ACEtk.ReferenceFrame]:
        """
        The reference frames
        """
    @property
    def xss_array(self) -> ...:
        """
        The xss array of the block
        """
class FullyIsotropicDistribution:
    """
    Fully isotropic angular distribution
    
    The FullyIsotropicDistribution class contains contains no data. It is a
    convenience interface object used in the AND block.
    """
    def __init__(self) -> None:
        """
        Initialise the block
        
        Arguments:
            self    the block
        """
class GeneralEvaporationSpectrum:
    """
    A general evaporation spectrum
    
    The GeneralEvaporationSpectrum class contains the tabulated energy and
    temperature values as well as the bin date used to describe the
    general evaporation spectrum. It is used in the DLW block as ACE LAW 5.
    """
    @typing.overload
    def __init__(self, boundaries: list[int], interpolants: list[int], energies: list[float], temperatures: list[float], bins: list[float]) -> None:
        """
        Initialise the block
        
        Arguments:
            self            the block
            boundaries      the interpolation range boundaries
            interpolants    the interpolation types for each range
            energies        the energy values
            temperatures    the temperature values
            bins            the x bin values
        """
    @typing.overload
    def __init__(self, energies: list[float], temperatures: list[float], bins: list[float]) -> None:
        """
        Initialise the block without interpolation data
        
        Arguments:
            self            the block
            energies        the energy values
            temperatures    the temperature values
            bins            the x bin values
        """
    @typing.overload
    def xss(self, index: int) -> float:
        """
        Return a value from the xss array of the block
        
        Arguments:
            self     the data block
            index    the index (one-based)
        """
    @typing.overload
    def xss(self, index: int, length: int) -> ...:
        """
        Return a subrange of a given length from the xss array of the block
        
        Arguments:
            self      the data block
            index     the index (one-based)
            length    the length of the subrange
        """
    @property
    def INT(self) -> ...:
        """
        The interpolation type for each range
        """
    @property
    def LAW(self) -> ACEtk.EnergyDistributionType:
        """
        The distribution type
        """
    @property
    def NB(self) -> int:
        """
        The number of interpolation regions
        """
    @property
    def NBT(self) -> ...:
        """
        The interpolation boundaries
        """
    @property
    def NE(self) -> int:
        """
        The number of incident energy values
        """
    @property
    def NET(self) -> int:
        """
        The number of x values
        """
    @property
    def bins(self) -> ...:
        """
        The equiprobable x bins
        """
    @property
    def boundaries(self) -> ...:
        """
        The interpolation boundaries
        """
    @property
    def empty(self) -> bool:
        """
        Whether or not the block is empty
        """
    @property
    def energies(self) -> ...:
        """
        The incident energy values
        """
    @property
    def interpolants(self) -> ...:
        """
        The interpolation type for each range
        """
    @property
    def interpolation_data(self) -> InterpolationData:
        """
        The interpolation data
        """
    @property
    def length(self) -> int:
        """
        The length of the the xss array of the block
        """
    @property
    def maximum_incident_energy(self) -> float:
        """
        The maximum incident energy for the distribution
        """
    @property
    def minimum_incident_energy(self) -> float:
        """
        The minimum incident energy for the distribution
        """
    @property
    def name(self) -> str:
        """
        The name of the block
        """
    @property
    def number_bins(self) -> int:
        """
        The number of x bins
        """
    @property
    def number_energy_points(self) -> int:
        """
        The number of incident energy values
        """
    @property
    def number_interpolation_regions(self) -> int:
        """
        The number of interpolation regions
        """
    @property
    def temperatures(self) -> ...:
        """
        The temperature values
        """
    @property
    def type(self) -> ACEtk.EnergyDistributionType:
        """
        The distribution type
        """
    @property
    def xss_array(self) -> ...:
        """
        The xss array of the block
        """
class InterpolationData:
    """
    Convenience interface for interpolation data
    """
    @typing.overload
    def xss(self, index: int) -> float:
        """
        Return a value from the xss array of the block
        
        Arguments:
            self     the data block
            index    the index (one-based)
        """
    @typing.overload
    def xss(self, index: int, length: int) -> ...:
        """
        Return a subrange of a given length from the xss array of the block
        
        Arguments:
            self      the data block
            index     the index (one-based)
            length    the length of the subrange
        """
    @property
    def INT(self) -> ...:
        """
        The interpolation type for each range
        """
    @property
    def NB(self) -> int:
        """
        The number of interpolation regions
        """
    @property
    def NBT(self) -> ...:
        """
        The interpolation boundaries
        """
    @property
    def boundaries(self) -> ...:
        """
        The interpolation boundaries
        """
    @property
    def empty(self) -> bool:
        """
        Whether or not the block is empty
        """
    @property
    def interpolants(self) -> ...:
        """
        The interpolation type for each range
        """
    @property
    def is_linear_linear(self) -> bool:
        """
        Flag to indicate whether or not the data is fully linear-linear
        """
    @property
    def length(self) -> int:
        """
        The length of the the xss array of the block
        """
    @property
    def name(self) -> str:
        """
        The name of the block
        """
    @property
    def number_interpolation_regions(self) -> int:
        """
        The number of interpolation regions
        """
    @property
    def xss_array(self) -> ...:
        """
        The xss array of the block
        """
class IsotropicAngularDistribution:
    """
    Isotropic angular distribution
    
    The IsotropicAngularDistribution class contains contains no data other than
    the incident energy. It is a convenience interface object used in the AND block
    """
    def __init__(self, energy: float) -> None:
        """
        Initialise the block
        
        Arguments:
            self      the block
            energy    the associated energy value
        """
    @property
    def energy(self) -> float:
        """
        The associated energy value
        """
class KalbachMannDistributionData:
    """
    Correlated outgoing energy-angle distribution data using Kalbach-Mann systematics
    
    The KalbachMannDistributionData class contains the Kalbach-Mann distributions
    for a set of incident energy values. It is used in the DLW block as ACE LAW 44.
    """
    def LOCC(self, index: int) -> int:
        """
        Return the the distribution locator for an incident energy index
        
        This locator is the value as stored in the XSS array. It is relative to
        the beginning of the DLW block.
        
        When the index is out of range an out of range exception is thrown
        (debug mode only).
        
            self     the block
            index    the index (one-based)
        """
    @typing.overload
    def __init__(self, distributions: list[TabulatedKalbachMannDistribution], locb: int = 1) -> None:
        """
        Initialise the block
        
        Arguments:
            self             the block
            distributions    the distributions for each incident energy
            locb             the starting xss index with respect to the DLW block
                             (default = 1, the relative locators get recalculated)
        """
    @typing.overload
    def __init__(self, boundaries: list[int], interpolants: list[int], distributions: list[TabulatedKalbachMannDistribution], locb: int = 1) -> None:
        """
        Initialise the block
        
        Arguments:
            self             the block
            boundaries       the interpolation range boundaries
            interpolants     the interpolation types for each range
            distributions    the distributions for each incident energy
            locb             the starting xss index with respect to the DLW block
                             (default = 1, the relative locators get recalculated)
        """
    def distribution(self, index: int) -> TabulatedKalbachMannDistribution:
        """
        Return the distribution data for an incident energy index
        
        When the index is out of range an out of range exception is thrown
        (debug mode only).
        
            self     the block
            index    the index (one-based)
        """
    def distribution_locator(self, index: int) -> int:
        """
        Return the the distribution locator for an incident energy index
        
        This locator is the value as stored in the XSS array. It is relative to
        the beginning of the DLW block.
        
        When the index is out of range an out of range exception is thrown
        (debug mode only).
        
            self     the block
            index    the index (one-based)
        """
    def incident_energy(self, index: int) -> float:
        """
        Return the incident energy for a given index
        
        When the index is out of range an out of range exception is thrown
        (debug mode only).
        
            self     the block
            index    the index (one-based)
        """
    def relative_distribution_locator(self, index: int) -> int:
        """
        Return the relative distribution locator for an incident energy index
        
        This is the locator relative to the beginning of the current angular
        distribution block in the DLW block. It is always positive.
        
        When the index is out of range an out of range exception is thrown
        (debug mode only).
        
            self     the block
            index    the index (one-based)
        """
    @typing.overload
    def xss(self, index: int) -> float:
        """
        Return a value from the xss array of the block
        
        Arguments:
            self     the data block
            index    the index (one-based)
        """
    @typing.overload
    def xss(self, index: int, length: int) -> ...:
        """
        Return a subrange of a given length from the xss array of the block
        
        Arguments:
            self      the data block
            index     the index (one-based)
            length    the length of the subrange
        """
    @property
    def INT(self) -> ...:
        """
        The interpolation type for each range
        """
    @property
    def LAW(self) -> ACEtk.EnergyDistributionType:
        """
        The distribution type
        """
    @property
    def NB(self) -> int:
        """
        The number of interpolation regions
        """
    @property
    def NBT(self) -> ...:
        """
        The interpolation boundaries
        """
    @property
    def NE(self) -> int:
        """
        The number of incident energy values
        """
    @property
    def boundaries(self) -> ...:
        """
        The interpolation boundaries
        """
    @property
    def empty(self) -> bool:
        """
        Whether or not the block is empty
        """
    @property
    def incident_energies(self) -> ...:
        """
        The incident energy values
        """
    @property
    def interpolants(self) -> ...:
        """
        The interpolation type for each range
        """
    @property
    def interpolation_data(self) -> InterpolationData:
        """
        The interpolation data
        """
    @property
    def length(self) -> int:
        """
        The length of the the xss array of the block
        """
    @property
    def maximum_incident_energy(self) -> float:
        """
        The maximum incident energy for the distribution
        """
    @property
    def minimum_incident_energy(self) -> float:
        """
        The minimum incident energy for the distribution
        """
    @property
    def name(self) -> str:
        """
        The name of the block
        """
    @property
    def number_incident_energies(self) -> int:
        """
        The number of incident energy values
        """
    @property
    def number_interpolation_regions(self) -> int:
        """
        The number of interpolation regions
        """
    @property
    def type(self) -> ACEtk.EnergyDistributionType:
        """
        The distribution type
        """
    @property
    def xss_array(self) -> ...:
        """
        The xss array of the block
        """
class LevelScatteringDistribution:
    """
    The energy distribution uses analytical level scattering
    
    The LevelScatteringDistribution class contains two parameter values that
    determine the level scattering distribution (in the centre of mass):
      Eprime = C2 * ( E - C1 )
    with:
      C1 = ( A + 1 ) / A * abs( Q )
      C2 = ( A / ( A + 1 ) )^2
    It is used in the DLW block as ACE LAW 3.
    """
    def __init__(self, emin: float, emax: float, c1: float, c2: float) -> None:
        """
        Initialise the block
        
        Arguments:
            self    the block
            emin    the minimum energy for the distribution
            emax    the maximum energy for the distribution
            c1      the value of C1 = ( A + 1 ) / A * abs( Q )
            c2      the value of C2 = ( A / ( A + 1 ) )^2
        """
    @typing.overload
    def xss(self, index: int) -> float:
        """
        Return a value from the xss array of the block
        
        Arguments:
            self     the data block
            index    the index (one-based)
        """
    @typing.overload
    def xss(self, index: int, length: int) -> ...:
        """
        Return a subrange of a given length from the xss array of the block
        
        Arguments:
            self      the data block
            index     the index (one-based)
            length    the length of the subrange
        """
    @property
    def C1(self) -> float:
        """
        The value of C1 = ( A + 1 ) / A * abs( Q )
        """
    @property
    def C2(self) -> float:
        """
        The value of C2 = ( A / ( A + 1 ) )^2
        """
    @property
    def LAW(self) -> ACEtk.EnergyDistributionType:
        """
        The distribution type
        """
    @property
    def empty(self) -> bool:
        """
        Whether or not the block is empty
        """
    @property
    def length(self) -> int:
        """
        The length of the the xss array of the block
        """
    @property
    def maximum_incident_energy(self) -> float:
        """
        The maximum incident energy for the distribution
        """
    @property
    def minimum_incident_energy(self) -> float:
        """
        The minimum incident energy for the distribution
        """
    @property
    def name(self) -> str:
        """
        The name of the block
        """
    @property
    def type(self) -> ACEtk.EnergyDistributionType:
        """
        The distribution type
        """
    @property
    def xss_array(self) -> ...:
        """
        The xss array of the block
        """
class MultiDistributionData:
    """
    The distribution is a combination of multiple distributions
    
    The MultiDistributionData class contains a set of distributions and
    associated probabilities to represent the particle's distribution data.
    This type of distribution is rarely used, and when it happens it is often
    used for higher chance fission spectra. It is used in the DLW block (there
    is no ACE LAW associated to this distribution type, but internally in ACEtk
    we refer to it as ACE LAW 666 because it is evil).
    """
    def __init__(self, probabilities: list[DistributionProbability], distributions: list[EquiprobableOutgoingEnergyBinData | DiscretePhotonDistribution | LevelScatteringDistribution | OutgoingEnergyDistributionData | GeneralEvaporationSpectrum | SimpleMaxwellianFissionSpectrum | EvaporationSpectrum | EnergyDependentWattSpectrum | KalbachMannDistributionData | NBodyPhaseSpaceDistribution | TwoBodyTransferDistribution | EnergyAngleDistributionData | AngleEnergyDistributionData], locb: int = 1) -> None:
        """
        Initialise the block
        
        Arguments:
            self             the block
            probabilities    the probabilities
            distributions    the distributions
            locb             the starting xss index with respect to the superblock
                             (default = 1, the relative locators get recalculated)
        """
    def distribution(self, index: int) -> EquiprobableOutgoingEnergyBinData | DiscretePhotonDistribution | LevelScatteringDistribution | OutgoingEnergyDistributionData | GeneralEvaporationSpectrum | SimpleMaxwellianFissionSpectrum | EvaporationSpectrum | EnergyDependentWattSpectrum | KalbachMannDistributionData | NBodyPhaseSpaceDistribution | TwoBodyTransferDistribution | EnergyAngleDistributionData | AngleEnergyDistributionData:
        """
        Return the distribution data for a distribution index
        
        When the index is out of range an out of range exception is thrown
        (debug mode only).
        
            self     the block
            index    the index (one-based)
        """
    def probability(self, index: int) -> DistributionProbability:
        """
        Return the probability data for a distribution index
        
        When the index is out of range an out of range exception is thrown
        (debug mode only).
        
            self     the block
            index    the index (one-based)
        """
    @typing.overload
    def xss(self, index: int) -> float:
        """
        Return a value from the xss array of the block
        
        Arguments:
            self     the data block
            index    the index (one-based)
        """
    @typing.overload
    def xss(self, index: int, length: int) -> ...:
        """
        Return a subrange of a given length from the xss array of the block
        
        Arguments:
            self      the data block
            index     the index (one-based)
            length    the length of the subrange
        """
    @property
    def LAW(self) -> ACEtk.EnergyDistributionType:
        """
        The distribution type
        """
    @property
    def distributions(self) -> list[EquiprobableOutgoingEnergyBinData | DiscretePhotonDistribution | LevelScatteringDistribution | OutgoingEnergyDistributionData | GeneralEvaporationSpectrum | SimpleMaxwellianFissionSpectrum | EvaporationSpectrum | EnergyDependentWattSpectrum | KalbachMannDistributionData | NBodyPhaseSpaceDistribution | TwoBodyTransferDistribution | EnergyAngleDistributionData | AngleEnergyDistributionData]:
        """
        The distribution data for each distribution
        """
    @property
    def empty(self) -> bool:
        """
        Whether or not the block is empty
        """
    @property
    def length(self) -> int:
        """
        The length of the the xss array of the block
        """
    @property
    def name(self) -> str:
        """
        The name of the block
        """
    @property
    def number_distributions(self) -> int:
        """
        The number of distributions
        """
    @property
    def probabilities(self) -> list[DistributionProbability]:
        """
        The probability data for each distribution
        """
    @property
    def type(self) -> ACEtk.EnergyDistributionType:
        """
        The distribution type
        """
    @property
    def xss_array(self) -> ...:
        """
        The xss array of the block
        """
class MultiplicityReactionNumberBlock:
    """
    The continuous energy YP block with the reaction MT numbers required for production cross section calculation
    
    The MultiplicityReactionNumberBlock class contains the reaction MT numbers
    that are needed in production cross section calculations using multiplicity
    values.
    """
    def MT(self, index: int) -> int:
        """
        The reaction number for a reaction index
        
        Arguments:
            self     the block
            index    the index (one-based)
        """
    def __init__(self, reactions: list[int]) -> None:
        """
        Initialise the block
        
        Arguments:
            self         the block
            reactions    the MT numbers
        """
    def has_MT(self, reaction: int) -> bool:
        """
        Return whether or not the reaction number is present
        
            self        the block
            reaction    the reaction number
        """
    def has_reaction_number(self, reaction: int) -> bool:
        """
        Return whether or not the reaction number is present
        
            self        the block
            reaction    the reaction number
        """
    def index(self, reaction: int) -> int:
        """
        Return the index (one-based) of the reaction number
        
            self        the block
            reaction    the reaction number
        """
    def reaction_number(self, index: int) -> int:
        """
        The reaction number for a reaction index
        
        Arguments:
            self     the block
            index    the index (one-based)
        """
    @typing.overload
    def xss(self, index: int) -> float:
        """
        Return a value from the xss array of the block
        
        Arguments:
            self     the data block
            index    the index (one-based)
        """
    @typing.overload
    def xss(self, index: int, length: int) -> ...:
        """
        Return a subrange of a given length from the xss array of the block
        
        Arguments:
            self      the data block
            index     the index (one-based)
            length    the length of the subrange
        """
    @property
    def MTs(self) -> ...:
        """
        The reaction numbers
        """
    @property
    def NYP(self) -> int:
        """
        The number of available reactions
        """
    @property
    def empty(self) -> bool:
        """
        Whether or not the block is empty
        """
    @property
    def length(self) -> int:
        """
        The length of the the xss array of the block
        """
    @property
    def name(self) -> str:
        """
        The name of the block
        """
    @property
    def number_reactions(self) -> int:
        """
        The number of available reactions
        """
    @property
    def reaction_numbers(self) -> ...:
        """
        The reaction numbers
        """
    @property
    def xss_array(self) -> ...:
        """
        The xss array of the block
        """
class NBodyPhaseSpaceDistribution:
    """
    The energy distribution uses the N-body phase space formalism
    
    The NBodyPhaseSpaceDistribution class contains two parameter values that
    determine the distribution: the number of particles in the system and the
    total mass ratio. It is used in the DLW block as ACE LAW 66.
    """
    def __init__(self, emin: float, emax: float, npsx: int, ap: float, interpolation: int, values: list[float], pdf: list[float], cdf: list[float]) -> None:
        """
        Initialise the block
        
        Arguments:
            self             the block
            emin             the minimum energy for the distribution
            emax             the maximum energy for the distribution
            npsx             the number of particles in the system
            ap               the total mass ratio
            interpolation    the interpolation flag
            values           the xi values
            pdf              the pdf values
            cdf              the cdf values
        """
    @typing.overload
    def xss(self, index: int) -> float:
        """
        Return a value from the xss array of the block
        
        Arguments:
            self     the data block
            index    the index (one-based)
        """
    @typing.overload
    def xss(self, index: int, length: int) -> ...:
        """
        Return a subrange of a given length from the xss array of the block
        
        Arguments:
            self      the data block
            index     the index (one-based)
            length    the length of the subrange
        """
    @property
    def AP(self) -> float:
        """
        The total mass ratio
        """
    @property
    def LAW(self) -> ACEtk.EnergyDistributionType:
        """
        The distribution type
        """
    @property
    def NPSX(self) -> int:
        """
        The number of particles in the system
        """
    @property
    def cdf(self) -> ...:
        """
        The cdf values
        """
    @property
    def empty(self) -> bool:
        """
        Whether or not the block is empty
        """
    @property
    def interpolation(self) -> int:
        """
        The interpolation flag
        """
    @property
    def length(self) -> int:
        """
        The length of the the xss array of the block
        """
    @property
    def maximum_incident_energy(self) -> float:
        """
        The maximum incident energy for the distribution
        """
    @property
    def minimum_incident_energy(self) -> float:
        """
        The minimum incident energy for the distribution
        """
    @property
    def name(self) -> str:
        """
        The name of the block
        """
    @property
    def number_particles(self) -> int:
        """
        The number of particles in the system
        """
    @property
    def number_values(self) -> int:
        """
        The number of values
        """
    @property
    def pdf(self) -> ...:
        """
        The pdf values
        """
    @property
    def total_mass_ratio(self) -> float:
        """
        The total mass ratio
        """
    @property
    def type(self) -> ACEtk.EnergyDistributionType:
        """
        The distribution type
        """
    @property
    def values(self) -> ...:
        """
        The normalised energy values
        """
    @property
    def xss_array(self) -> ...:
        """
        The xss array of the block
        """
class OutgoingEnergyDistributionData:
    """
    Outgoing energy distribution data using tabulated outgoing energy distributions
    
    The OutgoingEnergyDistributionData class contains the tabulated outgoing
    energy distributions for a set of incident energy values. It is used in
    the DLW block as ACE LAW 4.
    """
    def LOCC(self, index: int) -> int:
        """
        Return the the distribution locator for an incident energy index
        
        This locator is the value as stored in the XSS array. It is relative to
        the beginning of the DLW block.
        
        When the index is out of range an out of range exception is thrown
        (debug mode only).
        
            self     the block
            index    the index (one-based)
        """
    @typing.overload
    def __init__(self, distributions: list[TabulatedEnergyDistribution], locb: int = 1) -> None:
        """
        Initialise the block
        
        Arguments:
            self             the block
            distributions    the distributions for each incident energy
            locb             the starting xss index with respect to the DLW block
                             (default = 1, the relative locators get recalculated)
        """
    @typing.overload
    def __init__(self, boundaries: list[int], interpolants: list[int], distributions: list[TabulatedEnergyDistribution], locb: int = 1) -> None:
        """
        Initialise the block
        
        Arguments:
            self             the block
            boundaries       the interpolation range boundaries
            interpolants     the interpolation types for each range
            distributions    the distributions for each incident energy
            locb             the starting xss index with respect to the DLW block
                             (default = 1, the relative locators get recalculated)
        """
    def distribution(self, index: int) -> TabulatedEnergyDistribution:
        """
        Return the distribution data for an incident energy index
        
        When the index is out of range an out of range exception is thrown
        (debug mode only).
        
            self     the block
            index    the index (one-based)
        """
    def distribution_locator(self, index: int) -> int:
        """
        Return the the distribution locator for an incident energy index
        
        This locator is the value as stored in the XSS array. It is relative to
        the beginning of the DLW block.
        
        When the index is out of range an out of range exception is thrown
        (debug mode only).
        
            self     the block
            index    the index (one-based)
        """
    def incident_energy(self, index: int) -> float:
        """
        Return the incident energy for a given index
        
        When the index is out of range an out of range exception is thrown
        (debug mode only).
        
            self     the block
            index    the index (one-based)
        """
    def relative_distribution_locator(self, index: int) -> int:
        """
        Return the relative distribution locator for an incident energy index
        
        This is the locator relative to the beginning of the current angular
        distribution block in the DLW block. It is always positive.
        
        When the index is out of range an out of range exception is thrown
        (debug mode only).
        
            self     the block
            index    the index (one-based)
        """
    @typing.overload
    def xss(self, index: int) -> float:
        """
        Return a value from the xss array of the block
        
        Arguments:
            self     the data block
            index    the index (one-based)
        """
    @typing.overload
    def xss(self, index: int, length: int) -> ...:
        """
        Return a subrange of a given length from the xss array of the block
        
        Arguments:
            self      the data block
            index     the index (one-based)
            length    the length of the subrange
        """
    @property
    def INT(self) -> ...:
        """
        The interpolation type for each range
        """
    @property
    def LAW(self) -> ACEtk.EnergyDistributionType:
        """
        The distribution type
        """
    @property
    def NB(self) -> int:
        """
        The number of interpolation regions
        """
    @property
    def NBT(self) -> ...:
        """
        The interpolation boundaries
        """
    @property
    def NE(self) -> int:
        """
        The number of incident energy values
        """
    @property
    def boundaries(self) -> ...:
        """
        The interpolation boundaries
        """
    @property
    def empty(self) -> bool:
        """
        Whether or not the block is empty
        """
    @property
    def incident_energies(self) -> ...:
        """
        The incident energy values
        """
    @property
    def interpolants(self) -> ...:
        """
        The interpolation type for each range
        """
    @property
    def interpolation_data(self) -> InterpolationData:
        """
        The interpolation data
        """
    @property
    def length(self) -> int:
        """
        The length of the the xss array of the block
        """
    @property
    def maximum_incident_energy(self) -> float:
        """
        The maximum incident energy for the distribution
        """
    @property
    def minimum_incident_energy(self) -> float:
        """
        The minimum incident energy for the distribution
        """
    @property
    def name(self) -> str:
        """
        The name of the block
        """
    @property
    def number_incident_energies(self) -> int:
        """
        The number of incident energy values
        """
    @property
    def number_interpolation_regions(self) -> int:
        """
        The number of interpolation regions
        """
    @property
    def type(self) -> ACEtk.EnergyDistributionType:
        """
        The distribution type
        """
    @property
    def xss_array(self) -> ...:
        """
        The xss array of the block
        """
class ParameterData:
    """
    Parameter data for a Watt spectrum
    """
    @typing.overload
    def __init__(self, energies: list[float], values: list[float]) -> None:
        """
        Initialise the block assuming linear interpolation
        
        Arguments:
            self        the block
            energies    the energy values
            values      the parameter values
        """
    @typing.overload
    def __init__(self, boundaries: list[int], interpolants: list[int], energies: list[float], values: list[float]) -> None:
        """
        Initialise the block
        
        Arguments:
            self            the block
            boundaries      the interpolation range boundaries
            interpolants    the interpolation types for each range
            energies        the energy values
            values          the parameter values
        """
    @typing.overload
    def xss(self, index: int) -> float:
        """
        Return a value from the xss array of the block
        
        Arguments:
            self     the data block
            index    the index (one-based)
        """
    @typing.overload
    def xss(self, index: int, length: int) -> ...:
        """
        Return a subrange of a given length from the xss array of the block
        
        Arguments:
            self      the data block
            index     the index (one-based)
            length    the length of the subrange
        """
    @property
    def INT(self) -> ...:
        """
        The interpolation type for each range
        """
    @property
    def NB(self) -> int:
        """
        The number of interpolation regions
        """
    @property
    def NBT(self) -> ...:
        """
        The interpolation boundaries
        """
    @property
    def NE(self) -> int:
        """
        The number of energy values
        """
    @property
    def boundaries(self) -> ...:
        """
        The interpolation boundaries
        """
    @property
    def empty(self) -> bool:
        """
        Whether or not the block is empty
        """
    @property
    def energies(self) -> ...:
        """
        The energy values
        """
    @property
    def interpolants(self) -> ...:
        """
        The interpolation type for each range
        """
    @property
    def interpolation_data(self) -> InterpolationData:
        """
        The interpolation data
        """
    @property
    def length(self) -> int:
        """
        The length of the the xss array of the block
        """
    @property
    def name(self) -> str:
        """
        The name of the block
        """
    @property
    def number_energy_points(self) -> int:
        """
        The number of energy values
        """
    @property
    def number_interpolation_regions(self) -> int:
        """
        The number of interpolation regions
        """
    @property
    def values(self) -> ...:
        """
        The parameter values
        """
    @property
    def xss_array(self) -> ...:
        """
        The xss array of the block
        """
class PhotonProductionBlock:
    """
    The continuous energy GPD block with the total photon production cross section
    
    The PhotonProductionBlock class contains the total photon production cross
    section, given on the same energy grid as defined in the principal cross
    section block. For older data files, this also contains the equiprobable
    energy bins.
    """
    def __init__(self, production: list[float]) -> None:
        """
        Initialise the block
        
        Arguments:
            self          the block
            production    the total photon production cross section values
        """
    @typing.overload
    def xss(self, index: int) -> float:
        """
        Return a value from the xss array of the block
        
        Arguments:
            self     the data block
            index    the index (one-based)
        """
    @typing.overload
    def xss(self, index: int, length: int) -> ...:
        """
        Return a subrange of a given length from the xss array of the block
        
        Arguments:
            self      the data block
            index     the index (one-based)
            length    the length of the subrange
        """
    @property
    def NES(self) -> int:
        """
        The number of energy points
        """
    @property
    def empty(self) -> bool:
        """
        Whether or not the block is empty
        """
    @property
    def length(self) -> int:
        """
        The length of the the xss array of the block
        """
    @property
    def name(self) -> str:
        """
        The name of the block
        """
    @property
    def number_energy_points(self) -> int:
        """
        The number of energy points
        """
    @property
    def total_production(self) -> ...:
        """
        The total photon production cross section values
        """
    @property
    def xss_array(self) -> ...:
        """
        The xss array of the block
        """
class PhotonProductionCrossSectionBlock:
    """
    The PhotonProductionCrossSectionBlock class contains NXS(6) sets of photon
    production data, one for each reaction number on the MTRP block. The order
    of these cross section data sets is the same as the order of the reaction
    numbers in the MTRP block.
    """
    def LSIG(self, index: int) -> int:
        """
        Return the relative cross section locator for a reaction index
        
        When the index is out of range an out of range exception is thrown
        (debug mode only).
        
            self     the block
            index    the index (one-based)
        """
    def __init__(self, xs: list[PhotonProductionCrossSectionData | TabulatedSecondaryParticleMultiplicity]) -> None:
        """
        Initialise the block
        
        Arguments:
            self    the block
            xs      the cross section data
        """
    def cross_section_data(self, index: int) -> PhotonProductionCrossSectionData | TabulatedSecondaryParticleMultiplicity:
        """
        Return the cross section data for a reaction index
        
        When the index is out of range an out of range exception is thrown
        (debug mode only).
        
            self     the block
            index    the index (one-based)
        """
    def cross_section_locator(self, index: int) -> int:
        """
        Return the relative cross section locator for a reaction index
        
        When the index is out of range an out of range exception is thrown
        (debug mode only).
        
            self     the block
            index    the index (one-based)
        """
    @typing.overload
    def xss(self, index: int) -> float:
        """
        Return a value from the xss array of the block
        
        Arguments:
            self     the data block
            index    the index (one-based)
        """
    @typing.overload
    def xss(self, index: int, length: int) -> ...:
        """
        Return a subrange of a given length from the xss array of the block
        
        Arguments:
            self      the data block
            index     the index (one-based)
            length    the length of the subrange
        """
    @property
    def NTRP(self) -> int:
        """
        The number of photon production reactions
        """
    @property
    def data(self) -> list[PhotonProductionCrossSectionData | TabulatedSecondaryParticleMultiplicity]:
        """
        The cross section data
        """
    @property
    def empty(self) -> bool:
        """
        Whether or not the block is empty
        """
    @property
    def length(self) -> int:
        """
        The length of the the xss array of the block
        """
    @property
    def name(self) -> str:
        """
        The name of the block
        """
    @property
    def number_photon_production_reactions(self) -> int:
        """
        The number of photon production reactions
        """
    @property
    def xss_array(self) -> ...:
        """
        The xss array of the block
        """
class PhotonProductionCrossSectionData:
    """
    Photon production cross section data from the SIGP block for a single reaction
    """
    def __init__(self, index: int, values: list[float]) -> None:
        """
        Initialise the block
        
        Arguments:
            self      the block
            index     the energy index
            values    the cross section values
        """
    @typing.overload
    def xss(self, index: int) -> float:
        """
        Return a value from the xss array of the block
        
        Arguments:
            self     the data block
            index    the index (one-based)
        """
    @typing.overload
    def xss(self, index: int, length: int) -> ...:
        """
        Return a subrange of a given length from the xss array of the block
        
        Arguments:
            self      the data block
            index     the index (one-based)
            length    the length of the subrange
        """
    @property
    def MFTYPE(self) -> int:
        """
        The representation type (should always be 13)
        """
    @property
    def cross_sections(self) -> ...:
        """
        The cross section values
        """
    @property
    def empty(self) -> bool:
        """
        Whether or not the block is empty
        """
    @property
    def energy_index(self) -> int:
        """
        The energy index
        """
    @property
    def length(self) -> int:
        """
        The length of the the xss array of the block
        """
    @property
    def name(self) -> str:
        """
        The name of the block
        """
    @property
    def number_values(self) -> int:
        """
        The number of cross section values
        """
    @property
    def type(self) -> int:
        """
        The representation type (should always be 13)
        """
    @property
    def xss_array(self) -> ...:
        """
        The xss array of the block
        """
class PolynomialFissionMultiplicity:
    """
    Polynomial fission multiplicity
    
    The PolynomialFissionMultiplicity class contains the polynomial
    representation (LNU = 1) of the fission multiplicity. It is
    used in the NU block.
    """
    def __init__(self, coefficients: list[float]) -> None:
        """
        Initialise the block
        
        Arguments:
            self            the block
            coefficients    the polynomial coefficients
        """
    @typing.overload
    def xss(self, index: int) -> float:
        """
        Return a value from the xss array of the block
        
        Arguments:
            self     the data block
            index    the index (one-based)
        """
    @typing.overload
    def xss(self, index: int, length: int) -> ...:
        """
        Return a subrange of a given length from the xss array of the block
        
        Arguments:
            self      the data block
            index     the index (one-based)
            length    the length of the subrange
        """
    @property
    def C(self) -> ...:
        """
        The coefficients
        """
    @property
    def LNU(self) -> int:
        """
        The representation type (should always be 1)
        """
    @property
    def NC(self) -> int:
        """
        The number of polynomial coefficients
        """
    @property
    def coefficients(self) -> ...:
        """
        The coefficients
        """
    @property
    def empty(self) -> bool:
        """
        Whether or not the block is empty
        """
    @property
    def length(self) -> int:
        """
        The length of the the xss array of the block
        """
    @property
    def name(self) -> str:
        """
        The name of the block
        """
    @property
    def number_coefficients(self) -> int:
        """
        The number of polynomial coefficients
        """
    @property
    def type(self) -> int:
        """
        The representation type (should always be 1)
        """
    @property
    def xss_array(self) -> ...:
        """
        The xss array of the block
        """
class PrincipalCrossSectionBlock:
    """
    The continuous energy ESZ block with the principal cross sections
    
    The PrincipalCrossSectionBlock class contains 5 arrays of the same length:
      - the energy points
      - the total cross section
      - the elastic scattering cross section
      - the projectile disappearance cross section
      - the average heating numbers
    
    The size of each (the total number of energy points) is stored in NXS(3).
    """
    def __init__(self, energies: list[float], total: list[float], disappearance: list[float], elastic: list[float], heating: list[float]) -> None:
        """
        Initialise the block
        
        Arguments:
            self             the block
            energies         the energy values
            total            the total cross section values
            disappearance    the projectile disappearance cross section values
            elastic          the elastic cross section values
            heating          the average heating cross section values
        """
    @typing.overload
    def xss(self, index: int) -> float:
        """
        Return a value from the xss array of the block
        
        Arguments:
            self     the data block
            index    the index (one-based)
        """
    @typing.overload
    def xss(self, index: int, length: int) -> ...:
        """
        Return a subrange of a given length from the xss array of the block
        
        Arguments:
            self      the data block
            index     the index (one-based)
            length    the length of the subrange
        """
    @property
    def NES(self) -> int:
        """
        The number of energy points
        """
    @property
    def disappearance(self) -> ...:
        """
        The projectile disappearance cross section values
        """
    @property
    def elastic(self) -> ...:
        """
        The elastic cross section values
        """
    @property
    def empty(self) -> bool:
        """
        Whether or not the block is empty
        """
    @property
    def energies(self) -> ...:
        """
        The energy values
        """
    @property
    def heating(self) -> ...:
        """
        The average heating numbers
        """
    @property
    def length(self) -> int:
        """
        The length of the the xss array of the block
        """
    @property
    def name(self) -> str:
        """
        The name of the block
        """
    @property
    def number_energy_points(self) -> int:
        """
        The number of energy points
        """
    @property
    def total(self) -> ...:
        """
        The total cross section values
        """
    @property
    def xss_array(self) -> ...:
        """
        The xss array of the block
        """
class ProbabilityTable:
    """
    An unresolved resonance probability table for a single incident energy value
    
    The ProbabilityTable class contains the probabilities and associated
    values for the total, elastic, fission and capture cross sections and the
    heating numbers.
    """
    @typing.overload
    def __init__(self, incident: float, probabilities: list[float], total: list[float], elastic: list[float], capture: list[float], heating: list[float]) -> None:
        """
        Initialise the block
        
        Arguments:
            self             the block
            incident         the incident energy value
            probabilities    the probability values
            total            the total cross section values
            elastic          the elastic cross section values
            capture          the capture cross section values
            heating          the heating numbers
        """
    @typing.overload
    def __init__(self, incident: float, probabilities: list[float], total: list[float], elastic: list[float], fission: list[float], capture: list[float], heating: list[float]) -> None:
        """
        Initialise the block
        
        Arguments:
            self             the block
            incident         the incident energy value
            probabilities    the probability values
            total            the total cross section values
            elastic          the elastic cross section values
            fission          the fission cross section values
            capture          the capture cross section values
            heating          the heating numbers
        """
    @typing.overload
    def xss(self, index: int) -> float:
        """
        Return a value from the xss array of the block
        
        Arguments:
            self     the data block
            index    the index (one-based)
        """
    @typing.overload
    def xss(self, index: int, length: int) -> ...:
        """
        Return a subrange of a given length from the xss array of the block
        
        Arguments:
            self      the data block
            index     the index (one-based)
            length    the length of the subrange
        """
    @property
    def capture(self) -> ...:
        """
        The capture cross section values
        """
    @property
    def cumulative_probabilities(self) -> ...:
        """
        The cumulative probability values
        """
    @property
    def elastic(self) -> ...:
        """
        The elastic cross section values
        """
    @property
    def empty(self) -> bool:
        """
        Whether or not the block is empty
        """
    @property
    def fission(self) -> ...:
        """
        The fission cross section values
        """
    @property
    def heating(self) -> ...:
        """
        The average heating cross section values
        """
    @property
    def incident_energy(self) -> float:
        """
        The incident energy value
        """
    @property
    def length(self) -> int:
        """
        The length of the the xss array of the block
        """
    @property
    def name(self) -> str:
        """
        The name of the block
        """
    @property
    def number_bins(self) -> int:
        """
        The number of bins in the table
        """
    @property
    def total(self) -> ...:
        """
        The total cross section values
        """
    @property
    def xss_array(self) -> ...:
        """
        The xss array of the block
        """
class ProbabilityTableBlock:
    """
    The continuous energy UNR block with the unresolved resonance probability tables
    """
    def __init__(self, interpolation: int, inelastic: int, absorption: int, type: int, tables: list[ProbabilityTable]) -> None:
        """
        Initialise the block
        
        Arguments:
            self             the block
            interpolation    the interpolation type
            inelastic        the inelastic competition flag
            absorption       the absorption competition flag
            type             the probability table type
            tables           the probability tables
        """
    def probability_table(self, index: int) -> ProbabilityTable:
        """
        Return the probability table for an incident energy index
        
        When the index is out of range an out of range exception is thrown
        (debug mode only).
        
            self     the block
            index    the index (one-based)
        """
    @typing.overload
    def xss(self, index: int) -> float:
        """
        Return a value from the xss array of the block
        
        Arguments:
            self     the data block
            index    the index (one-based)
        """
    @typing.overload
    def xss(self, index: int, length: int) -> ...:
        """
        Return a subrange of a given length from the xss array of the block
        
        Arguments:
            self      the data block
            index     the index (one-based)
            length    the length of the subrange
        """
    @property
    def IFF(self) -> int:
        """
        The table type (values or multipliers)
        """
    @property
    def ILF(self) -> int:
        """
        The inelastic competition flag
        """
    @property
    def INT(self) -> int:
        """
        The interpolation flag
        """
    @property
    def IOA(self) -> int:
        """
        The absorption competition flag
        """
    @property
    def M(self) -> int:
        """
        The number of bins in each table
        """
    @property
    def N(self) -> int:
        """
        The number of incident energy values
        """
    @property
    def absorption_competition(self) -> int:
        """
        The absorption competition flag
        """
    @property
    def data(self) -> list[ProbabilityTable]:
        """
        The probability tables
        """
    @property
    def empty(self) -> bool:
        """
        Whether or not the block is empty
        """
    @property
    def energies(self) -> ...:
        """
        The incident energy values
        """
    @property
    def inelastic_competition(self) -> int:
        """
        The inelastic competition flag
        """
    @property
    def interpolation(self) -> int:
        """
        The interpolation flag
        """
    @property
    def length(self) -> int:
        """
        The length of the the xss array of the block
        """
    @property
    def name(self) -> str:
        """
        The name of the block
        """
    @property
    def number_bins(self) -> int:
        """
        The number of bins in each table
        """
    @property
    def number_incident_energies(self) -> int:
        """
        The number of incident energy values
        """
    @property
    def type(self) -> int:
        """
        The table type (values or multipliers)
        """
    @property
    def xss_array(self) -> ...:
        """
        The xss array of the block
        """
class ReactionNumberBlock:
    """
    The continuous energy MTR block with the reaction MT numbers
    
    The ReactionNumberBlock class contains the reaction MT numbers for all
    available reactions (excluding elastic)
    
    The number of available reactions (excluding elastic) is stored in NXS(4).
    """
    def MT(self, index: int) -> int:
        """
        The reaction number for a reaction index
        
        Arguments:
            self     the block
            index    the index (one-based)
        """
    def __init__(self, reactions: list[int]) -> None:
        """
        Initialise the block
        
        Arguments:
            self         the block
            reactions    the MT numbers
        """
    def has_MT(self, reaction: int) -> bool:
        """
        Return whether or not the reaction number is present
        
            self        the block
            reaction    the reaction number
        """
    def has_reaction_number(self, reaction: int) -> bool:
        """
        Return whether or not the reaction number is present
        
            self        the block
            reaction    the reaction number
        """
    def index(self, reaction: int) -> int:
        """
        Return the index (one-based) of the reaction number
        
            self        the block
            reaction    the reaction number
        """
    def reaction_number(self, index: int) -> int:
        """
        The reaction number for a reaction index
        
        Arguments:
            self     the block
            index    the index (one-based)
        """
    @typing.overload
    def xss(self, index: int) -> float:
        """
        Return a value from the xss array of the block
        
        Arguments:
            self     the data block
            index    the index (one-based)
        """
    @typing.overload
    def xss(self, index: int, length: int) -> ...:
        """
        Return a subrange of a given length from the xss array of the block
        
        Arguments:
            self      the data block
            index     the index (one-based)
            length    the length of the subrange
        """
    @property
    def MTs(self) -> ...:
        """
        The reaction numbers
        """
    @property
    def NTR(self) -> int:
        """
        The number of available reactions (excluding elastic)
        """
    @property
    def empty(self) -> bool:
        """
        Whether or not the block is empty
        """
    @property
    def length(self) -> int:
        """
        The length of the the xss array of the block
        """
    @property
    def name(self) -> str:
        """
        The name of the block
        """
    @property
    def number_reactions(self) -> int:
        """
        The number of available reactions (excluding elastic)
        """
    @property
    def reaction_numbers(self) -> ...:
        """
        The reaction numbers
        """
    @property
    def xss_array(self) -> ...:
        """
        The xss array of the block
        """
class ReactionQValueBlock:
    """
    The continuous energy LQR block with the reaction Q values
    
    The ReactionQValueBlock class contains the reaction Q values for all
    available reactions (excluding elastic). The order of these Q values
    is the same as the order of the reaction numbers in the MTR block.
    
    The number of available reactions (excluding elastic) is stored in NXS(4).
    """
    def __init__(self, qvalues: list[float]) -> None:
        """
        Initialise the block
        
        Arguments:
            self       the block
            qvalues    the Q values
        """
    def q_value(self, index: int) -> float:
        """
        The reaction Q value for a reaction index
        
        Arguments:
            self     the block
            index    the index (one-based)
        """
    @typing.overload
    def xss(self, index: int) -> float:
        """
        Return a value from the xss array of the block
        
        Arguments:
            self     the data block
            index    the index (one-based)
        """
    @typing.overload
    def xss(self, index: int, length: int) -> ...:
        """
        Return a subrange of a given length from the xss array of the block
        
        Arguments:
            self      the data block
            index     the index (one-based)
            length    the length of the subrange
        """
    @property
    def NTR(self) -> int:
        """
        The number of available reactions (excluding elastic)
        """
    @property
    def empty(self) -> bool:
        """
        Whether or not the block is empty
        """
    @property
    def length(self) -> int:
        """
        The length of the the xss array of the block
        """
    @property
    def name(self) -> str:
        """
        The name of the block
        """
    @property
    def number_reactions(self) -> int:
        """
        The number of available reactions (excluding elastic)
        """
    @property
    def q_values(self) -> ...:
        """
        The reaction Q values
        """
    @property
    def xss_array(self) -> ...:
        """
        The xss array of the block
        """
class SecondaryParticleAngularDistributionBlock:
    """
    The continuous energy LANDP, ANDP and LANDH, ANDH blocks with the
    angular distribution data for secondary particles that are not the
    incident particle type
    
    The SecondaryParticleAngularDistributionBlock class contains angular
    distribution data, one for each the NXS(6) reaction numbers on the MTRP
    block (for the LANDP, ANDP blocks) and each of the NTRO(ITYPE) reactions on
    the MTRH(ITYPE) block. The order of the distribution data sets is the same
    as the order of the reaction numbers in the corresponding MTR block.
    """
    def LAND(self, index: int) -> int:
        """
        Return the relative angular distribution locator for a reaction index
        
        When the index is out of range an out of range exception is thrown
        (debug mode only).
        
            self     the block
            index    the index (one-based, zero for elastic)
        """
    def __init__(self, distributions: list[FullyIsotropicDistribution | DistributionGivenElsewhere | AngularDistributionData]) -> None:
        """
        Initialise the block
        
        Arguments:
            self             the block
            distributions    the angular distribution data
        """
    def angular_distribution_data(self, index: int) -> FullyIsotropicDistribution | DistributionGivenElsewhere | AngularDistributionData:
        """
        Return the angular distribution data for a reaction index
        
        When the index is out of range an out of range exception is thrown
        (debug mode only).
        
            self     the block
            index    the index (one-based, zero for elastic)
        """
    def angular_distribution_locator(self, index: int) -> int:
        """
        Return the relative angular distribution locator for a reaction index
        
        When the index is out of range an out of range exception is thrown
        (debug mode only).
        
            self     the block
            index    the index (one-based, zero for elastic)
        """
    def is_fully_isotropic(self, index: int) -> bool:
        """
        Return whether or not the distribution data is fully isotropic for
        a reaction index
        
        When the index is out of range an out of range exception is thrown
        (debug mode only).
        
            self     the block
            index    the index (one-based, zero for elastic)
        """
    def is_given(self, index: int) -> bool:
        """
        Return whether or not the distribution data is given in the AND block
        
        When the index is out of range an out of range exception is thrown
        (debug mode only).
        
            self     the block
            index    the index (one-based, zero for elastic)
        """
    @typing.overload
    def xss(self, index: int) -> float:
        """
        Return a value from the xss array of the block
        
        Arguments:
            self     the data block
            index    the index (one-based)
        """
    @typing.overload
    def xss(self, index: int, length: int) -> ...:
        """
        Return a subrange of a given length from the xss array of the block
        
        Arguments:
            self      the data block
            index     the index (one-based)
            length    the length of the subrange
        """
    @property
    def NR(self) -> int:
        """
        The number of reactions with angular distribution data
        """
    @property
    def data(self) -> list[FullyIsotropicDistribution | DistributionGivenElsewhere | AngularDistributionData]:
        """
        All angular distribution data
        """
    @property
    def empty(self) -> bool:
        """
        Whether or not the block is empty
        """
    @property
    def length(self) -> int:
        """
        The length of the the xss array of the block
        """
    @property
    def name(self) -> str:
        """
        The name of the block
        """
    @property
    def number_reactions(self) -> int:
        """
        The number of reactions with angular distribution data
        """
    @property
    def xss_array(self) -> ...:
        """
        The xss array of the block
        """
class SecondaryParticleEnergyDistributionBlock:
    """
    The continuous energy LDLWP, DLWP and LDLWH, DLWH blocks with the
    energy distribution data for secondary particles that are not the
    incident particle type
    
    The SecondaryParticleAngularDistributionBlock class contains energy
    distribution data, one for each the NXS(6) reaction numbers on the MTRP
    block (for the LANDP, ANDP blocks) and each of the NTRO(ITYPE) reactions on
    the MTRH(ITYPE) block. The order of the distribution data sets is the same
    as the order of the reaction numbers in the corresponding MTR block.
    """
    def LDLW(self, index: int) -> int:
        """
        Return the relative energy distribution locator for a reaction index
        
        When the index is out of range an out of range exception is thrown
        (debug mode only).
        
            self     the block
            index    the index (one-based)
        """
    @typing.overload
    def __init__(self, distributions: list[EquiprobableOutgoingEnergyBinData | DiscretePhotonDistribution | LevelScatteringDistribution | OutgoingEnergyDistributionData | GeneralEvaporationSpectrum | SimpleMaxwellianFissionSpectrum | EvaporationSpectrum | EnergyDependentWattSpectrum | KalbachMannDistributionData | NBodyPhaseSpaceDistribution | TwoBodyTransferDistribution | EnergyAngleDistributionData | AngleEnergyDistributionData | MultiDistributionData | UndefinedDistribution]) -> None:
        """
        Initialise the DNED block
        
        Arguments:
            self              the block
            distributions     the energy distribution data
        """
    @typing.overload
    def __init__(self, distributions: list[EquiprobableOutgoingEnergyBinData | DiscretePhotonDistribution | LevelScatteringDistribution | OutgoingEnergyDistributionData | GeneralEvaporationSpectrum | SimpleMaxwellianFissionSpectrum | EvaporationSpectrum | EnergyDependentWattSpectrum | KalbachMannDistributionData | NBodyPhaseSpaceDistribution | TwoBodyTransferDistribution | EnergyAngleDistributionData | AngleEnergyDistributionData | MultiDistributionData | UndefinedDistribution], frames: list[ACEtk.ReferenceFrame]) -> None:
        """
        Initialise the DLWH block
        
        Arguments:
            self              the block
            distributions     the energy distribution data
            frames            the reference frames
        """
    def energy_distribution_data(self, index: int) -> EquiprobableOutgoingEnergyBinData | DiscretePhotonDistribution | LevelScatteringDistribution | OutgoingEnergyDistributionData | GeneralEvaporationSpectrum | SimpleMaxwellianFissionSpectrum | EvaporationSpectrum | EnergyDependentWattSpectrum | KalbachMannDistributionData | NBodyPhaseSpaceDistribution | TwoBodyTransferDistribution | EnergyAngleDistributionData | AngleEnergyDistributionData | MultiDistributionData | UndefinedDistribution:
        """
        Return the energy distribution data for a reaction index
        
        When the index is out of range an out of range exception is thrown
        (debug mode only).
        
            self     the block
            index    the index (one-based)
        """
    def energy_distribution_locator(self, index: int) -> int:
        """
        Return the relative energy distribution locator for a reaction index
        
        When the index is out of range an out of range exception is thrown
        (debug mode only).
        
            self     the block
            index    the index (one-based)
        """
    def reference_frame(self, index: int) -> ACEtk.ReferenceFrame | None:
        """
        Return the reference frame for a reaction index
        
        When the index is out of range an out of range exception is thrown
        (debug mode only).
        
            self     the block
            index    the index (one-based)
        """
    @typing.overload
    def xss(self, index: int) -> float:
        """
        Return a value from the xss array of the block
        
        Arguments:
            self     the data block
            index    the index (one-based)
        """
    @typing.overload
    def xss(self, index: int, length: int) -> ...:
        """
        Return a subrange of a given length from the xss array of the block
        
        Arguments:
            self      the data block
            index     the index (one-based)
            length    the length of the subrange
        """
    @property
    def NR(self) -> int:
        """
        The number of reactions with energy distribution data
        """
    @property
    def data(self) -> list[EquiprobableOutgoingEnergyBinData | DiscretePhotonDistribution | LevelScatteringDistribution | OutgoingEnergyDistributionData | GeneralEvaporationSpectrum | SimpleMaxwellianFissionSpectrum | EvaporationSpectrum | EnergyDependentWattSpectrum | KalbachMannDistributionData | NBodyPhaseSpaceDistribution | TwoBodyTransferDistribution | EnergyAngleDistributionData | AngleEnergyDistributionData | MultiDistributionData | UndefinedDistribution]:
        """
        The energy distribution data
        """
    @property
    def empty(self) -> bool:
        """
        Whether or not the block is empty
        """
    @property
    def length(self) -> int:
        """
        The length of the the xss array of the block
        """
    @property
    def name(self) -> str:
        """
        The name of the block
        """
    @property
    def number_reactions(self) -> int:
        """
        The number of reactions with energy distribution data
        """
    @property
    def reference_frames(self) -> list[ACEtk.ReferenceFrame | None]:
        """
        The reference frames
        """
    @property
    def xss_array(self) -> ...:
        """
        The xss array of the block
        """
class SecondaryParticleInformationBlock:
    """
    The continuous energy NTRO block with the number of reactions for each secondary particle type
    
    The SecondaryParticleInformationBlock class contains the number of reactions
    that produce each secondary particle type as given on the PTYPE.
    The number of available particle types is stored in NXS(7).
    """
    def NP(self, index: int) -> int:
        """
        The number of reactions for a secondary particle index
        
        Arguments:
            self     the block
            index    the index (one-based)
        """
    def __init__(self, numbers: list[int]) -> None:
        """
        Initialise the block
        
        Arguments:
            self       the block
            numbers    the number of reaction for each particle type
        """
    def number_secondary_particle_production_reactions(self, index: int) -> int:
        """
        The number of reactions for a secondary particle index
        
        Arguments:
            self     the block
            index    the index (one-based)
        """
    @typing.overload
    def xss(self, index: int) -> float:
        """
        Return a value from the xss array of the block
        
        Arguments:
            self     the data block
            index    the index (one-based)
        """
    @typing.overload
    def xss(self, index: int, length: int) -> ...:
        """
        Return a subrange of a given length from the xss array of the block
        
        Arguments:
            self      the data block
            index     the index (one-based)
            length    the length of the subrange
        """
    @property
    def NPs(self) -> ...:
        """
        The number of reactions for each particle type
        """
    @property
    def NTYPE(self) -> int:
        """
        The number of secondary particle types (excluding the projectile and photons)
        """
    @property
    def empty(self) -> bool:
        """
        Whether or not the block is empty
        """
    @property
    def length(self) -> int:
        """
        The length of the the xss array of the block
        """
    @property
    def name(self) -> str:
        """
        The name of the block
        """
    @property
    def number_additional_secondary_particle_types(self) -> int:
        """
        The number of secondary particle types (excluding the projectile and photons)
        """
    @property
    def number_reactions(self) -> ...:
        """
        The number of reactions for each particle type
        """
    @property
    def xss_array(self) -> ...:
        """
        The xss array of the block
        """
class SecondaryParticleLocatorBlock:
    """
    The continuous energy IXS block with the secondary particle locators
    
    The SecondaryParticleLocatorBlock class contains 10 locators for each
    secondary particle type as given on the PTYPE block.
    The number of available particle types is stored in NXS(7).
    """
    def ANDH(self, index: int) -> int:
        """
        The locator to the ANDH block for a secondary particle index
        
        Arguments:
            self     the block
            index    the secondary particle index (one-based)
        """
    def DLWH(self, index: int) -> int:
        """
        The locator to the DLWH block for a secondary particle index
        
        Arguments:
            self     the block
            index    the secondary particle index (one-based)
        """
    def HPD(self, index: int) -> int:
        """
        The locator to the HPD block for a secondary particle index
        
        Arguments:
            self     the block
            index    the secondary particle index (one-based)
        """
    def LANDH(self, index: int) -> int:
        """
        The locator to the LANDH block for a secondary particle index
        
        Arguments:
            self     the block
            index    the secondary particle index (one-based)
        """
    def LDLWH(self, index: int) -> int:
        """
        The locator to the LDLWH block for a secondary particle index
        
        Arguments:
            self     the block
            index    the secondary particle index (one-based)
        """
    def LLOC(self, particle: int, index: int) -> int:
        """
        The locator for a secondary particle index and block index
        
        Arguments:
            self        the block
            particle    the secondary particle index (one-based)    index       the block index (one-based)
        """
    def LSIGH(self, index: int) -> int:
        """
        The locator to the LSIGH block for a secondary particle index
        
        Arguments:
            self     the block
            index    the secondary particle index (one-based)
        """
    def MTRH(self, index: int) -> int:
        """
        The locator to the MTRH block for a secondary particle index
        
        Arguments:
            self     the block
            index    the secondary particle index (one-based)
        """
    def SIGH(self, index: int) -> int:
        """
        The locator to the SIGH block for a secondary particle index
        
        Arguments:
            self     the block
            index    the secondary particle index (one-based)
        """
    def TYRH(self, index: int) -> int:
        """
        The locator to the TYRH block for a secondary particle index
        
        Arguments:
            self     the block
            index    the secondary particle index (one-based)
        """
    def YP(self, index: int) -> int:
        """
        The locator to the YP block for a secondary particle index
        
        Arguments:
            self     the block
            index    the secondary particle index (one-based)
        """
    def __init__(self, locators: list[list[int[10]]]) -> None:
        """
        Initialise the block
        
        Arguments:
            self       the block
            locators   the locators for each particle type
        """
    def locator(self, particle: int, index: int) -> int:
        """
        The locator for a secondary particle index and block index
        
        Arguments:
            self        the block
            particle    the secondary particle index (one-based)    index       the block index (one-based)
        """
    @typing.overload
    def xss(self, index: int) -> float:
        """
        Return a value from the xss array of the block
        
        Arguments:
            self     the data block
            index    the index (one-based)
        """
    @typing.overload
    def xss(self, index: int, length: int) -> ...:
        """
        Return a subrange of a given length from the xss array of the block
        
        Arguments:
            self      the data block
            index     the index (one-based)
            length    the length of the subrange
        """
    @property
    def NTYPE(self) -> int:
        """
        The number of secondary particle types (excluding the projectile)
        """
    @property
    def empty(self) -> bool:
        """
        Whether or not the block is empty
        """
    @property
    def length(self) -> int:
        """
        The length of the the xss array of the block
        """
    @property
    def name(self) -> str:
        """
        The name of the block
        """
    @property
    def number_additional_secondary_particle_types(self) -> int:
        """
        The number of secondary particle types (excluding the projectile)
        """
    @property
    def xss_array(self) -> ...:
        """
        The xss array of the block
        """
class SecondaryParticleProductionBlock:
    """
    Total production cross section and heating numbers for a secondary particle
    """
    def __init__(self, index: int, production: list[float], heating: list[float]) -> None:
        """
        Initialise the block
        
        Arguments:
            self          the block
            index         the energy index
            production    the total production cross section values    heating       the heating numbers
        """
    @typing.overload
    def xss(self, index: int) -> float:
        """
        Return a value from the xss array of the block
        
        Arguments:
            self     the data block
            index    the index (one-based)
        """
    @typing.overload
    def xss(self, index: int, length: int) -> ...:
        """
        Return a subrange of a given length from the xss array of the block
        
        Arguments:
            self      the data block
            index     the index (one-based)
            length    the length of the subrange
        """
    @property
    def empty(self) -> bool:
        """
        Whether or not the block is empty
        """
    @property
    def energy_index(self) -> int:
        """
        The energy index
        """
    @property
    def heating(self) -> ...:
        """
        The heating numbers
        """
    @property
    def length(self) -> int:
        """
        The length of the the xss array of the block
        """
    @property
    def name(self) -> str:
        """
        The name of the block
        """
    @property
    def number_values(self) -> int:
        """
        The number of cross section values
        """
    @property
    def total_production(self) -> ...:
        """
        The total poduction cross section values
        """
    @property
    def xss_array(self) -> ...:
        """
        The xss array of the block
        """
class SecondaryParticleProductionCrossSectionBlock:
    """
    The continuous energy LSIGH and SIGH block with the secondary particle
    production cross section data (multiplicity data only)
    
    The SecondaryParticleProductionCrossSectionBlock class contains NTRO.NP sets
    of secondary particle production data, one for each reaction number on the
    MTRH block. The order of these cross section data sets is the same as the
    order of the reaction numbers in the MTRH block.
    """
    def LSIG(self, index: int) -> int:
        """
        Return the relative cross section locator for a reaction index
        
        When the index is out of range an out of range exception is thrown
        (debug mode only).
        
            self     the block
            index    the index (one-based)
        """
    def __init__(self, xs: list[TabulatedSecondaryParticleMultiplicity]) -> None:
        """
        Initialise the block
        
        Arguments:
            self    the block
            xs      the cross section data
        """
    def cross_section_data(self, index: int) -> TabulatedSecondaryParticleMultiplicity:
        """
        Return the cross section data for a reaction index
        
        When the index is out of range an out of range exception is thrown
        (debug mode only).
        
            self     the block
            index    the index (one-based)
        """
    def cross_section_locator(self, index: int) -> int:
        """
        Return the relative cross section locator for a reaction index
        
        When the index is out of range an out of range exception is thrown
        (debug mode only).
        
            self     the block
            index    the index (one-based)
        """
    @typing.overload
    def xss(self, index: int) -> float:
        """
        Return a value from the xss array of the block
        
        Arguments:
            self     the data block
            index    the index (one-based)
        """
    @typing.overload
    def xss(self, index: int, length: int) -> ...:
        """
        Return a subrange of a given length from the xss array of the block
        
        Arguments:
            self      the data block
            index     the index (one-based)
            length    the length of the subrange
        """
    @property
    def NP(self) -> int:
        """
        The number of secondary particle production reactions
        """
    @property
    def data(self) -> list[TabulatedSecondaryParticleMultiplicity]:
        """
        The cross section data
        """
    @property
    def empty(self) -> bool:
        """
        Whether or not the block is empty
        """
    @property
    def length(self) -> int:
        """
        The length of the the xss array of the block
        """
    @property
    def name(self) -> str:
        """
        The name of the block
        """
    @property
    def number_secondary_particle_production_reactions(self) -> int:
        """
        The number of secondary particle production reactions
        """
    @property
    def xss_array(self) -> ...:
        """
        The xss array of the block
        """
class SecondaryParticleTypeBlock:
    """
    The continuous energy PTYPE block with the secondary particle types
    
    The SecondaryParticleTypeBlock class contains the secondary particle types
    for which data is available (excluding the incident particle type).
    The number of available particle types is stored in NXS(7).
    """
    def IP(self, index: int) -> int:
        """
        The particle type for a secondary particle index
        
        Arguments:
            self     the block
            index    the index (one-based)
        """
    def __init__(self, types: list[int]) -> None:
        """
        Initialise the block
        
        Arguments:
            self     the block
            types    the particle types
        """
    def has_IP(self, type: int) -> bool:
        """
        Return whether or not the particle type is present
        
            self    the block
            type    the particle type
        """
    def has_particle_type(self, type: int) -> bool:
        """
        Return whether or not the particle type is present
        
            self    the block
            type    the particle type
        """
    def index(self, type: int) -> int:
        """
        Return the index (one-based) of the particle type
        
            self    the block
            type    the particle type
        """
    def particle_type(self, index: int) -> int:
        """
        The particle type for a secondary particle index
        
        Arguments:
            self     the block
            index    the index (one-based)
        """
    @typing.overload
    def xss(self, index: int) -> float:
        """
        Return a value from the xss array of the block
        
        Arguments:
            self     the data block
            index    the index (one-based)
        """
    @typing.overload
    def xss(self, index: int, length: int) -> ...:
        """
        Return a subrange of a given length from the xss array of the block
        
        Arguments:
            self      the data block
            index     the index (one-based)
            length    the length of the subrange
        """
    @property
    def IPs(self) -> ...:
        """
        The particle types
        """
    @property
    def NTYPE(self) -> int:
        """
        The number of secondary particle types (excluding the projectile)
        """
    @property
    def empty(self) -> bool:
        """
        Whether or not the block is empty
        """
    @property
    def length(self) -> int:
        """
        The length of the the xss array of the block
        """
    @property
    def name(self) -> str:
        """
        The name of the block
        """
    @property
    def number_additional_secondary_particle_types(self) -> int:
        """
        The number of secondary particle types (excluding the projectile)
        """
    @property
    def particle_types(self) -> ...:
        """
        The particle types
        """
    @property
    def xss_array(self) -> ...:
        """
        The xss array of the block
        """
class SimpleMaxwellianFissionSpectrum:
    """
    A simple Maxwellian fission spectrum
    
    The SimpleMaxwellianFissionSpectrum class contains the tabulated energy and
    temperature values as well as the restriction energy U used to describe the
    Maxwellian fission spectrum. It is used in the DLW block as ACE LAW 7.
    """
    @typing.overload
    def __init__(self, boundaries: list[int], interpolants: list[int], energies: list[float], temperatures: list[float], energy: float) -> None:
        """
        Initialise the block
        
        Arguments:
            self            the block
            boundaries      the interpolation range boundaries
            interpolants    the interpolation types for each range
            energies        the energy values
            temperatures    the temperature values
            energy          the restriction energy
        """
    @typing.overload
    def __init__(self, energies: list[float], temperatures: list[float], energy: float) -> None:
        """
        Initialise the block without interpolation data
        
        Arguments:
            self            the block
            energies        the energy values
            temperatures    the temperature values
            energy          the restriction energy
        """
    @typing.overload
    def xss(self, index: int) -> float:
        """
        Return a value from the xss array of the block
        
        Arguments:
            self     the data block
            index    the index (one-based)
        """
    @typing.overload
    def xss(self, index: int, length: int) -> ...:
        """
        Return a subrange of a given length from the xss array of the block
        
        Arguments:
            self      the data block
            index     the index (one-based)
            length    the length of the subrange
        """
    @property
    def INT(self) -> ...:
        """
        The interpolation type for each range
        """
    @property
    def LAW(self) -> ACEtk.EnergyDistributionType:
        """
        The distribution type
        """
    @property
    def NB(self) -> int:
        """
        The number of interpolation regions
        """
    @property
    def NBT(self) -> ...:
        """
        The interpolation boundaries
        """
    @property
    def NE(self) -> int:
        """
        The number of incident energy values
        """
    @property
    def U(self) -> float:
        """
        The restriction energy
        """
    @property
    def boundaries(self) -> ...:
        """
        The interpolation boundaries
        """
    @property
    def empty(self) -> bool:
        """
        Whether or not the block is empty
        """
    @property
    def energies(self) -> ...:
        """
        The incident energy values
        """
    @property
    def interpolants(self) -> ...:
        """
        The interpolation type for each range
        """
    @property
    def interpolation_data(self) -> InterpolationData:
        """
        The interpolation data
        """
    @property
    def length(self) -> int:
        """
        The length of the the xss array of the block
        """
    @property
    def maximum_incident_energy(self) -> float:
        """
        The maximum incident energy for the distribution
        """
    @property
    def minimum_incident_energy(self) -> float:
        """
        The minimum incident energy for the distribution
        """
    @property
    def name(self) -> str:
        """
        The name of the block
        """
    @property
    def number_energy_points(self) -> int:
        """
        The number of incident energy values
        """
    @property
    def number_interpolation_regions(self) -> int:
        """
        The number of interpolation regions
        """
    @property
    def restriction_energy(self) -> float:
        """
        The restriction energy
        """
    @property
    def temperatures(self) -> ...:
        """
        The temperature values
        """
    @property
    def type(self) -> ACEtk.EnergyDistributionType:
        """
        The distribution type
        """
    @property
    def xss_array(self) -> ...:
        """
        The xss array of the block
        """
class TabulatedAngleEnergyDistribution:
    """
    Tabulated outgoing energy and angle distribution data for a single incident energy
    
    The TabulatedAngleEnergyDistribution class contains the tabulated outgoing
    energy distributions for a set of cosine values and associated incident
    energy value. It is used in the AngleEnergyDistributionData (ACE LAW 67)
    in the DLW block.
    """
    def LOCC(self, index: int) -> int:
        """
        Return the the distribution locator for a cosine index
        
        This locator is the value as stored in the XSS array. It is relative to
        the beginning of the DLW block.
        
        When the index is out of range an out of range exception is thrown
        (debug mode only).
        
            self     the block
            index    the index (one-based)
        """
    def __init__(self, incident: float, interpolation: int, distributions: list[TabulatedEnergyDistribution], locb: int = 1) -> None:
        """
        Initialise the block
        
        Arguments:
            self             the block
            incident         the incident energy value
            interpolation    the interpolation type
            distributions    the distributions for each outgoing energy
            locb             the starting xss index with respect to the DLW block
                             (default = 1, the relative locators get recalculated)
        """
    def cosine(self, index: int) -> float:
        """
        Return the cosine for a given index
        
        When the index is out of range an out of range exception is thrown
        (debug mode only).
        
            self     the block
            index    the index (one-based)
        """
    def distribution(self, index: int) -> TabulatedEnergyDistribution:
        """
        Return the distribution data for a cosine index
        
        When the index is out of range an out of range exception is thrown
        (debug mode only).
        
            self     the block
            index    the index (one-based)
        """
    def distribution_locator(self, index: int) -> int:
        """
        Return the the distribution locator for a cosine index
        
        This locator is the value as stored in the XSS array. It is relative to
        the beginning of the DLW block.
        
        When the index is out of range an out of range exception is thrown
        (debug mode only).
        
            self     the block
            index    the index (one-based)
        """
    def relative_distribution_locator(self, index: int) -> int:
        """
        Return the relative distribution locator for a cosine index
        
        This is the locator relative to the beginning of the current angular
        distribution block in the DLW block. It is always positive.
        
        When the index is out of range an out of range exception is thrown
        (debug mode only).
        
            self     the block
            index    the index (one-based)
        """
    @typing.overload
    def xss(self, index: int) -> float:
        """
        Return a value from the xss array of the block
        
        Arguments:
            self     the data block
            index    the index (one-based)
        """
    @typing.overload
    def xss(self, index: int, length: int) -> ...:
        """
        Return a subrange of a given length from the xss array of the block
        
        Arguments:
            self      the data block
            index     the index (one-based)
            length    the length of the subrange
        """
    @property
    def NC(self) -> int:
        """
        The number of cosine values
        """
    @property
    def cosines(self) -> ...:
        """
        The cosine values
        """
    @property
    def distributions(self) -> list[TabulatedEnergyDistribution]:
        """
        The distributions
        """
    @property
    def empty(self) -> bool:
        """
        Whether or not the block is empty
        """
    @property
    def incident_energy(self) -> float:
        """
        The incident energy value
        """
    @property
    def interpolation(self) -> int:
        """
        The interpolation type
        """
    @property
    def length(self) -> int:
        """
        The length of the the xss array of the block
        """
    @property
    def name(self) -> str:
        """
        The name of the block
        """
    @property
    def number_cosines(self) -> int:
        """
        The number of cosine values
        """
    @property
    def xss_array(self) -> ...:
        """
        The xss array of the block
        """
class TabulatedAngularDistribution:
    """
    Tabulated angular distribution data for a single incident or outgoing energy
    The TabulatedAngularDistribution class contains the probability density
    function (PDF) and cumulative density function (CDF) as a function of
    cosine for the given energy. It is used in the AND block.
    """
    def __init__(self, energy: float, interpolation: int, cosines: list[float], pdf: list[float], cdf: list[float]) -> None:
        """
        Initialise the block
        
        Arguments:
            self            the block
            energy          the associated energy value
            interpolation   the interpolation type
            cosines         the cosine values
            pdf             the pdf values
            cdf             the cdf values
        """
    @typing.overload
    def xss(self, index: int) -> float:
        """
        Return a value from the xss array of the block
        
        Arguments:
            self     the data block
            index    the index (one-based)
        """
    @typing.overload
    def xss(self, index: int, length: int) -> ...:
        """
        Return a subrange of a given length from the xss array of the block
        
        Arguments:
            self      the data block
            index     the index (one-based)
            length    the length of the subrange
        """
    @property
    def cdf(self) -> ...:
        """
        The cdf values
        """
    @property
    def cosines(self) -> ...:
        """
        The cosine values
        """
    @property
    def empty(self) -> bool:
        """
        Whether or not the block is empty
        """
    @property
    def energy(self) -> float:
        """
        The associated energy value
        """
    @property
    def interpolation(self) -> int:
        """
        The interpolation flag
        """
    @property
    def length(self) -> int:
        """
        The length of the the xss array of the block
        """
    @property
    def name(self) -> str:
        """
        The name of the block
        """
    @property
    def number_cosines(self) -> int:
        """
        The number of cosine values
        """
    @property
    def pdf(self) -> ...:
        """
        The pdf values
        """
    @property
    def xss_array(self) -> ...:
        """
        The xss array of the block
        """
class TabulatedAngularDistributionWithProbability:
    """
    Tabulated angular distribution data for a single incident or outgoing energy
    The TabulatedAngularDistributionWithProbability class contains the probability
    density function (PDF) and cumulative density function (CDF) as a function of
    cosine for the given energy and associated probability and cumulative probability.
    It is used in the OutgoingEnergyAngleDistributionData (ACE LAW 61) in the DLW block.
    """
    def __init__(self, energy: float, probability: float, cumulative: float, interpolation: int, cosines: list[float], pdf: list[float], cdf: list[float]) -> None:
        """
        Initialise the block
        
        Arguments:
            self           the block
            energy         the associated energy value
            probability    the associated probability value
            cumulative     the associated cumulative probability value
            cosines        the cosine values
            pdf            the pdf values
            cdf            the cdf values
        """
    @typing.overload
    def xss(self, index: int) -> float:
        """
        Return a value from the xss array of the block
        
        Arguments:
            self     the data block
            index    the index (one-based)
        """
    @typing.overload
    def xss(self, index: int, length: int) -> ...:
        """
        Return a subrange of a given length from the xss array of the block
        
        Arguments:
            self      the data block
            index     the index (one-based)
            length    the length of the subrange
        """
    @property
    def cdf(self) -> ...:
        """
        The cdf values
        """
    @property
    def cosines(self) -> ...:
        """
        The cosine values
        """
    @property
    def cumulative_probability(self) -> float:
        """
        The associated cumulative probability value
        """
    @property
    def empty(self) -> bool:
        """
        Whether or not the block is empty
        """
    @property
    def energy(self) -> float:
        """
        The associated energy value
        """
    @property
    def interpolation(self) -> int:
        """
        The interpolation flag
        """
    @property
    def length(self) -> int:
        """
        The length of the the xss array of the block
        """
    @property
    def name(self) -> str:
        """
        The name of the block
        """
    @property
    def number_cosines(self) -> int:
        """
        The number of cosine values
        """
    @property
    def pdf(self) -> ...:
        """
        The pdf values
        """
    @property
    def probability(self) -> float:
        """
        The associated probability value
        """
    @property
    def xss_array(self) -> ...:
        """
        The xss array of the block
        """
class TabulatedEnergyAngleDistribution:
    """
    Tabulated outgoing energy and angle distribution data for a single incident energy
    
    The TabulatedEnergyAngleDistribution class contains the tabulated angular
    distributions for a set of outgoing energy values and associated incident
    energy value. It is used in the OutgoingEnergyAngleDistributionData
    (ACE LAW 61) in the DLW block.
    """
    def LOCC(self, index: int) -> int:
        """
        Return the the distribution locator for an outgoing energy index
        
        This locator is the value as stored in the XSS array. It is relative to
        the beginning of the DLW block.
        
        When the index is out of range an out of range exception is thrown
        (debug mode only).
        
            self     the block
            index    the index (one-based)
        """
    def __init__(self, incident: float, interpolation: int, distributions: list[TabulatedAngularDistributionWithProbability], locb: int = 1) -> None:
        """
        Initialise the block
        
        Arguments:
            self             the block
            incident         the incident energy value
            interpolation    the interpolation type
            distributions    the distributions for each outgoing energy
            locb             the starting xss index with respect to the DLW block
                             (default = 1, the relative locators get recalculated)
        """
    def cumulative_probability(self, index: int) -> float:
        """
        Return the cumulative probability for a given index
        
        When the index is out of range an out of range exception is thrown
        (debug mode only).
        
            self     the block
            index    the index (one-based)
        """
    def distribution(self, index: int) -> TabulatedAngularDistributionWithProbability:
        """
        Return the distribution data for an outgoing energy index
        
        When the index is out of range an out of range exception is thrown
        (debug mode only).
        
            self     the block
            index    the index (one-based)
        """
    def distribution_locator(self, index: int) -> int:
        """
        Return the the distribution locator for an outgoing energy index
        
        This locator is the value as stored in the XSS array. It is relative to
        the beginning of the DLW block.
        
        When the index is out of range an out of range exception is thrown
        (debug mode only).
        
            self     the block
            index    the index (one-based)
        """
    def outgoing_energy(self, index: int) -> float:
        """
        Return the outgoing energy for a given index
        
        When the index is out of range an out of range exception is thrown
        (debug mode only).
        
            self     the block
            index    the index (one-based)
        """
    def probability(self, index: int) -> float:
        """
        Return the probability for a given index
        
        When the index is out of range an out of range exception is thrown
        (debug mode only).
        
            self     the block
            index    the index (one-based)
        """
    def relative_distribution_locator(self, index: int) -> int:
        """
        Return the relative distribution locator for an outgoing energy index
        
        This is the locator relative to the beginning of the current angular
        distribution block in the DLW block. It is always positive.
        
        When the index is out of range an out of range exception is thrown
        (debug mode only).
        
            self     the block
            index    the index (one-based)
        """
    @typing.overload
    def xss(self, index: int) -> float:
        """
        Return a value from the xss array of the block
        
        Arguments:
            self     the data block
            index    the index (one-based)
        """
    @typing.overload
    def xss(self, index: int, length: int) -> ...:
        """
        Return a subrange of a given length from the xss array of the block
        
        Arguments:
            self      the data block
            index     the index (one-based)
            length    the length of the subrange
        """
    @property
    def NE(self) -> int:
        """
        The number of outgoing energy values
        """
    @property
    def cdf(self) -> ...:
        """
        The associated cumulative probability values
        """
    @property
    def distributions(self) -> list[TabulatedAngularDistributionWithProbability]:
        """
        The distributions
        """
    @property
    def empty(self) -> bool:
        """
        Whether or not the block is empty
        """
    @property
    def incident_energy(self) -> float:
        """
        The incident energy value
        """
    @property
    def interpolation(self) -> int:
        """
        The interpolation type
        """
    @property
    def length(self) -> int:
        """
        The length of the the xss array of the block
        """
    @property
    def name(self) -> str:
        """
        The name of the block
        """
    @property
    def number_outgoing_energies(self) -> int:
        """
        The number of outgoing energy values
        """
    @property
    def outgoing_energies(self) -> ...:
        """
        The outgoing energy values
        """
    @property
    def pdf(self) -> ...:
        """
        The associated probability values
        """
    @property
    def xss_array(self) -> ...:
        """
        The xss array of the block
        """
class TabulatedEnergyDistribution:
    """
    Tabulated angular distribution data for a single incident energy or cosine value
    
    The TabulatedEnergyDistribution class contains the probability
    density function (PDF) and cumulative density function (CDF) as a function
    of the outgoing energy for the given incident energy or cosine value. It is
    used in the OutgoingEnergyDistributionData (ACE LAW 4 for a given incident
    energy) and in the OutgoingAngleEnergyDistributionData (ACE LAW 67 for a
    given cosine) in the DLW block.
    """
    def __init__(self, value: float, interpolation: int, cosines: list[float], pdf: list[float], cdf: list[float], discrete: int = 0) -> None:
        """
        Initialise the block
        
        Arguments:
            self        the block
            incident    the incident energy or cosine value
            outgoing    the outgoing energy values
            pdf         the pdf values
            cdf         the cdf values
            discrete    the number of discrete photon lines (defaults to 0)
        """
    @typing.overload
    def xss(self, index: int) -> float:
        """
        Return a value from the xss array of the block
        
        Arguments:
            self     the data block
            index    the index (one-based)
        """
    @typing.overload
    def xss(self, index: int, length: int) -> ...:
        """
        Return a subrange of a given length from the xss array of the block
        
        Arguments:
            self      the data block
            index     the index (one-based)
            length    the length of the subrange
        """
    @property
    def cdf(self) -> ...:
        """
        The cdf values
        """
    @property
    def empty(self) -> bool:
        """
        Whether or not the block is empty
        """
    @property
    def energy_or_cosine(self) -> float:
        """
        The incident energy
        """
    @property
    def interpolation(self) -> int:
        """
        The interpolation flag
        """
    @property
    def length(self) -> int:
        """
        The length of the the xss array of the block
        """
    @property
    def name(self) -> str:
        """
        The name of the block
        """
    @property
    def number_discrete_photon_lines(self) -> int:
        """
        The number of discrete photon lines
        """
    @property
    def number_outgoing_energies(self) -> int:
        """
        The number of outgoing energy values
        """
    @property
    def outgoing_energies(self) -> ...:
        """
        The outgoing energy values
        """
    @property
    def pdf(self) -> ...:
        """
        The pdf values
        """
    @property
    def xss_array(self) -> ...:
        """
        The xss array of the block
        """
class TabulatedFissionMultiplicity:
    """
    Tabulated fission multiplicity
    
    The TabulatedFissionMultiplicity class contains the tabulated
    representation (LNU = 2) of the fission multiplicity. It is
    used in the NU block.
    """
    @typing.overload
    def __init__(self, energies: list[float], multiplicities: list[float]) -> None:
        """
        Initialise the block assuming linear interpolation
        
        Arguments:
            self             the block
            energies         the energy values
            multiplicities   the multiplicity values
        """
    @typing.overload
    def __init__(self, boundaries: list[int], interpolants: list[int], energies: list[float], multiplicities: list[float]) -> None:
        """
        Initialise the block
        
        Arguments:
            self             the block
            boundaries       the interpolation range boundaries
            interpolants     the interpolation types for each range
            energies         the energy values
            multiplicities   the multiplicity values
        """
    @typing.overload
    def xss(self, index: int) -> float:
        """
        Return a value from the xss array of the block
        
        Arguments:
            self     the data block
            index    the index (one-based)
        """
    @typing.overload
    def xss(self, index: int, length: int) -> ...:
        """
        Return a subrange of a given length from the xss array of the block
        
        Arguments:
            self      the data block
            index     the index (one-based)
            length    the length of the subrange
        """
    @property
    def E(self) -> ...:
        """
        The energy values
        """
    @property
    def INT(self) -> ...:
        """
        The interpolants
        """
    @property
    def LNU(self) -> int:
        """
        The representation type (should always be 2)
        """
    @property
    def NB(self) -> int:
        """
        The number of interpolation regions
        """
    @property
    def NBT(self) -> ...:
        """
        The interpolation boundaries
        """
    @property
    def NE(self) -> int:
        """
        The number of values
        """
    @property
    def NU(self) -> ...:
        """
        The multiplicities
        """
    @property
    def boundaries(self) -> ...:
        """
        The interpolation boundaries
        """
    @property
    def empty(self) -> bool:
        """
        Whether or not the block is empty
        """
    @property
    def energies(self) -> ...:
        """
        The energy values
        """
    @property
    def interpolants(self) -> ...:
        """
        The interpolants
        """
    @property
    def interpolation_data(self) -> InterpolationData:
        """
        The interpolation data
        """
    @property
    def length(self) -> int:
        """
        The length of the the xss array of the block
        """
    @property
    def multiplicities(self) -> ...:
        """
        The multiplicities
        """
    @property
    def name(self) -> str:
        """
        The name of the block
        """
    @property
    def number_interpolation_regions(self) -> int:
        """
        The number of interpolation regions
        """
    @property
    def number_values(self) -> int:
        """
        The number of values
        """
    @property
    def type(self) -> int:
        """
        The representation type (should always be 2)
        """
    @property
    def xss_array(self) -> ...:
        """
        The xss array of the block
        """
class TabulatedKalbachMannDistribution:
    """
    Tabulated Kalbach-Mann distribution data for a single incident energy
    
    The TabulatedKalbachMannDistribution class contains the probability
    density function (PDF), the cumulative density function (CDF), the
    precompound fraction r and angular distribution slope a as a function
    of the outgoing energy for a single incident energy. It is
    used in the KalbachMannDistributionData (ACE LAW 44 for a given incident
    energy) in the DLW block.
    """
    def __init__(self, incident: float, interpolation: int, cosines: list[float], pdf: list[float], cdf: list[float], r: list[float], a: list[float], discrete: int = 0) -> None:
        """
        Initialise the block
        
        Arguments:
            self        the block
            incident    the incident energy value
            cosines     the cosine values
            pdf         the pdf values
            cdf         the cdf values
            r           the precompound fraction values values
            a           the angular distribution slope values
            discrete    the number of discrete photon lines (defaults to 0)
        """
    @typing.overload
    def xss(self, index: int) -> float:
        """
        Return a value from the xss array of the block
        
        Arguments:
            self     the data block
            index    the index (one-based)
        """
    @typing.overload
    def xss(self, index: int, length: int) -> ...:
        """
        Return a subrange of a given length from the xss array of the block
        
        Arguments:
            self      the data block
            index     the index (one-based)
            length    the length of the subrange
        """
    @property
    def angular_distribution_slope_values(self) -> ...:
        """
        The angular distribution slope values
        """
    @property
    def cdf(self) -> ...:
        """
        The cdf values
        """
    @property
    def empty(self) -> bool:
        """
        Whether or not the block is empty
        """
    @property
    def incident_energy(self) -> float:
        """
        The incident energy
        """
    @property
    def interpolation(self) -> int:
        """
        The interpolation flag
        """
    @property
    def length(self) -> int:
        """
        The length of the the xss array of the block
        """
    @property
    def name(self) -> str:
        """
        The name of the block
        """
    @property
    def number_discrete_photon_lines(self) -> int:
        """
        The number of discrete photon lines
        """
    @property
    def number_outgoing_energies(self) -> int:
        """
        The number of outgoing energy values
        """
    @property
    def outgoing_energies(self) -> ...:
        """
        The outgoing energy values
        """
    @property
    def pdf(self) -> ...:
        """
        The pdf values
        """
    @property
    def precompound_fraction_values(self) -> ...:
        """
        The precompound fraction values
        """
    @property
    def xss_array(self) -> ...:
        """
        The xss array of the block
        """
class TabulatedMultiplicity:
    """
    Tabulated multiplicity data (used in the DLW block)
    """
    @typing.overload
    def __init__(self, energies: list[float], multiplicities: list[float]) -> None:
        """
        Initialise the block assuming linear interpolation
        
        Arguments:
            self              the block
            energies          the energy values
            multiplicities    the multiplicity values
        """
    @typing.overload
    def __init__(self, boundaries: list[int], interpolants: list[int], energies: list[float], multiplicities: list[float]) -> None:
        """
        Initialise the block
        
        Arguments:
            self              the block
            boundaries        the interpolation range boundaries
            interpolants      the interpolation types for each range
            energies          the energy values
            multiplicities    the multiplicity values
        """
    @typing.overload
    def xss(self, index: int) -> float:
        """
        Return a value from the xss array of the block
        
        Arguments:
            self     the data block
            index    the index (one-based)
        """
    @typing.overload
    def xss(self, index: int, length: int) -> ...:
        """
        Return a subrange of a given length from the xss array of the block
        
        Arguments:
            self      the data block
            index     the index (one-based)
            length    the length of the subrange
        """
    @property
    def INT(self) -> ...:
        """
        The interpolation type for each range
        """
    @property
    def NB(self) -> int:
        """
        The number of interpolation regions
        """
    @property
    def NBT(self) -> ...:
        """
        The interpolation boundaries
        """
    @property
    def NE(self) -> int:
        """
        The number of energy values
        """
    @property
    def boundaries(self) -> ...:
        """
        The interpolation boundaries
        """
    @property
    def empty(self) -> bool:
        """
        Whether or not the block is empty
        """
    @property
    def energies(self) -> ...:
        """
        The energy values
        """
    @property
    def interpolants(self) -> ...:
        """
        The interpolation type for each range
        """
    @property
    def interpolation_data(self) -> InterpolationData:
        """
        The interpolation data
        """
    @property
    def length(self) -> int:
        """
        The length of the the xss array of the block
        """
    @property
    def multiplicities(self) -> ...:
        """
        The multiplicity values
        """
    @property
    def name(self) -> str:
        """
        The name of the block
        """
    @property
    def number_energy_points(self) -> int:
        """
        The number of energy values
        """
    @property
    def number_interpolation_regions(self) -> int:
        """
        The number of interpolation regions
        """
    @property
    def xss_array(self) -> ...:
        """
        The xss array of the block
        """
class TabulatedSecondaryParticleMultiplicity:
    """
    Tabulated secondary particle multiplicity
    
    The TabulatedSecondaryParticleMultiplicity class contains tabulated
    multiplicities for a secondary particle (MFMULT = 12 or 16). It also
    contains the MT number of the associated reaction.
    """
    @typing.overload
    def __init__(self, mftype: int, mt: int, energies: list[float], multiplicities: list[float]) -> None:
        """
        Initialise the block assuming linear interpolation
        
        Arguments:
            self             the block
            mftype           the type (12 or 16)
            mt               the associated reaction number
            energies         the energy values
            multiplicities   the multiplicity values
        """
    @typing.overload
    def __init__(self, mftype: int, mt: int, boundaries: list[int], interpolants: list[int], energies: list[float], xs: list[float]) -> None:
        """
        Initialise the block
        
        Arguments:
            self            the block
            mftype          the type (12 or 16)
            mt              the associated reaction number
            boundaries      the interpolation range boundaries
            interpolants    the interpolation types for each range
            energies        the energy values
            xs              the xs values
        """
    @typing.overload
    def xss(self, index: int) -> float:
        """
        Return a value from the xss array of the block
        
        Arguments:
            self     the data block
            index    the index (one-based)
        """
    @typing.overload
    def xss(self, index: int, length: int) -> ...:
        """
        Return a subrange of a given length from the xss array of the block
        
        Arguments:
            self      the data block
            index     the index (one-based)
            length    the length of the subrange
        """
    @property
    def E(self) -> ...:
        """
        The energy values
        """
    @property
    def INT(self) -> ...:
        """
        The interpolants
        """
    @property
    def MFTYPE(self) -> int:
        """
        The representation type (should always be 12 or 16))
        """
    @property
    def MT(self) -> int:
        """
        The associated reaction number
        """
    @property
    def NB(self) -> int:
        """
        The number of interpolation regions
        """
    @property
    def NBT(self) -> ...:
        """
        The interpolation boundaries
        """
    @property
    def NE(self) -> int:
        """
        The number of values
        """
    @property
    def NU(self) -> ...:
        """
        The multiplicities
        """
    @property
    def boundaries(self) -> ...:
        """
        The interpolation boundaries
        """
    @property
    def empty(self) -> bool:
        """
        Whether or not the block is empty
        """
    @property
    def energies(self) -> ...:
        """
        The energy values
        """
    @property
    def interpolants(self) -> ...:
        """
        The interpolants
        """
    @property
    def interpolation_data(self) -> InterpolationData:
        """
        The interpolation data
        """
    @property
    def length(self) -> int:
        """
        The length of the the xss array of the block
        """
    @property
    def multiplicities(self) -> ...:
        """
        The multiplicities
        """
    @property
    def name(self) -> str:
        """
        The name of the block
        """
    @property
    def number_interpolation_regions(self) -> int:
        """
        The number of interpolation regions
        """
    @property
    def number_values(self) -> int:
        """
        The number of values
        """
    @property
    def reaction_number(self) -> int:
        """
        The associated reaction number
        """
    @property
    def type(self) -> int:
        """
        The representation type (should always be 12 or 16))
        """
    @property
    def xss_array(self) -> ...:
        """
        The xss array of the block
        """
class TwoBodyTransferDistribution:
    """
    The energy distribution uses two body transfer
    
    It is used in the DLW block as ACE LAW 33.
    """
    def __init__(self, emin: float, emax: float, c1: float, c2: float) -> None:
        """
        Initialise the block
        
        Arguments:
            self    the block
            emin    the minimum energy for the distribution
            emax    the maximum energy for the distribution
            c1      the value of C1
            c2      the value of C2
        """
    @typing.overload
    def xss(self, index: int) -> float:
        """
        Return a value from the xss array of the block
        
        Arguments:
            self     the data block
            index    the index (one-based)
        """
    @typing.overload
    def xss(self, index: int, length: int) -> ...:
        """
        Return a subrange of a given length from the xss array of the block
        
        Arguments:
            self      the data block
            index     the index (one-based)
            length    the length of the subrange
        """
    @property
    def C1(self) -> float:
        """
        The value of C1
        """
    @property
    def C2(self) -> float:
        """
        The value of C2
        """
    @property
    def LAW(self) -> ACEtk.EnergyDistributionType:
        """
        The distribution type
        """
    @property
    def empty(self) -> bool:
        """
        Whether or not the block is empty
        """
    @property
    def length(self) -> int:
        """
        The length of the the xss array of the block
        """
    @property
    def maximum_incident_energy(self) -> float:
        """
        The maximum incident energy for the distribution
        """
    @property
    def minimum_incident_energy(self) -> float:
        """
        The minimum incident energy for the distribution
        """
    @property
    def name(self) -> str:
        """
        The name of the block
        """
    @property
    def type(self) -> ACEtk.EnergyDistributionType:
        """
        The distribution type
        """
    @property
    def xss_array(self) -> ...:
        """
        The xss array of the block
        """
class UndefinedDistribution:
    """
    The distribution is undefined
    
    The UndefinedDistribution class contains no data. It is a convenience
    interface object used in the DLWH block when no energy distribution data
    is given.
    """
    def __init__(self) -> None:
        """
        Initialise the block
        
        Arguments:
            self    the block
        """
