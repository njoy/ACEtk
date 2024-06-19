/**
 *  @brief Insert or replace the NU block
 *
 *  @param[in] nu    the fission neutron multiplicity block to be inserted
 */
void insertOrReplace( continuous::NU nu ) {

  this->data() = generateData( this->Z(), this->A(), this->S(),
                               std::move( this->esz_ ),
                               std::move( nu ),
                               std::move( this->mtr_ ),
                               std::move( this->lqr_ ),
                               std::move( this->sig_ ),
                               std::move( this->and_ ),
                               std::move( this->dlw_ ),
                               std::move( this->gpd_ ),
                               std::move( this->mtrp_ ),
                               std::move( this->sigp_ ),
                               std::move( this->andp_ ),
                               std::move( this->dlwp_ ),
                               std::move( this->yp_ ),
                               std::move( this->unr_ ),
                               std::move( this->dnu_ ),
                               std::move( this->bdd_ ),
                               std::move( this->dned_ ),
                               std::move( this->ptype_ ),
                               std::move( this->hpd_ ),
                               std::move( this->mtrh_ ),
                               std::move( this->sigh_ ),
                               std::move( this->andh_ ),
                               std::move( this->dlwh_ ),
                               std::move( this->yh_  ) );
  this->generateBlocks();
}
